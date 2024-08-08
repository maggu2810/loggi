//
// Created by maggu2810 on 8/5/24.
//

#include <loggi/loggi_impl.hxx>

#include <loggi/loggi_compat_unreachable.hxx>

#define SD_JOURNAL_SUPPRESS_LOCATION
#include <systemd/sd-journal.h>

#include <filesystem>
#include <sstream>
#include <cstdio>
#include <functional>
#include <unistd.h>

namespace {
    int syslogLevel(loggi::level level) {
        switch (level) {
            case loggi::level::emergency:
                return LOG_EMERG;
            case loggi::level::alert:
                return LOG_ALERT;
            case loggi::level::critical:
                return LOG_CRIT;
            case loggi::level::error:
                return LOG_ERR;
            case loggi::level::warning:
                return LOG_WARNING;
            case loggi::level::notice:
                return LOG_NOTICE;
            case loggi::level::info:
                return LOG_INFO;
            case loggi::level::debug:
                return LOG_DEBUG;
        }
        LOGGI_UNREACHABLE();
    }

    bool directly_invoked_by_systemd() {
        const char *systemd_exec_pid = std::getenv("SYSTEMD_EXEC_PID");
        if (systemd_exec_pid == nullptr) {
            return ::getppid() == 1;
        } else {
            return std::to_string(::getpid()) == systemd_exec_pid;
        }
    }

    using logfunc = std::function<void(const loggi::impl::Opaque &opaque, loggi::level lvl,
                                       const std::string &str)>;

    logfunc createStreamLogger(FILE *stream) {
        return [stream](const loggi::impl::Opaque &opaque, loggi::level lvl, const std::string &str) -> void {
            const auto &sloc_opt = opaque.sloc();
            std::stringstream ss;
            if (sloc_opt) {
                const auto &sloc = *sloc_opt;
                ss << "[" << std::filesystem::path(sloc.file_name()).filename().generic_string() << ":" << sloc.line()
                        << ":" << sloc.column() << "] ";
            }
            ss << "level: " << static_cast<int>(lvl) << " => " << str << "\n";
            std::fprintf(stream, "%s", ss.str().data());
        };
    }

    logfunc createJournalLogger() {
        return [](const loggi::impl::Opaque &opaque, loggi::level lvl, const std::string &str) -> void {
            const auto &sloc_opt = opaque.sloc();

            std::vector<std::string> entries;

            entries.push_back(slog_fmt_ns::format("MESSAGE={}", str));
            entries.push_back(slog_fmt_ns::format("PRIORITY={}", syslogLevel(lvl)));
            if (opaque.tid()) {
                std::stringstream ss;
                ss << "TID=";
                ss << *opaque.tid();
                entries.push_back(ss.str());
            }

            int iovcnt = static_cast<int>(entries.size());
            struct iovec iov[iovcnt];
            for (int i = 0; i < iovcnt; ++i) {
                iov[i].iov_base = entries[i].data();
                iov[i].iov_len = entries[i].length();
            }

            int err;
            if (opaque.sloc()) {
                err = sd_journal_sendv_with_location(
                    slog_fmt_ns::format("CODE_FILE={}", sloc_opt->file_name()).data(),
                    slog_fmt_ns::format("CODE_LINE={}", sloc_opt->line()).data(),
                    sloc_opt->function_name(), iov, iovcnt);
            } else {
                err = sd_journal_sendv(iov, iovcnt);
            }

            if (err) {
                const int errno_last = errno;
                std::fprintf(stderr, "send to sd_journal failed: err: %d, errno: %d\n", err, errno_last);
            }
        };
    }

    logfunc createNullLogger() {
        return [](const loggi::impl::Opaque &opaque, loggi::level lvl, const std::string &str) -> void {
        };
    }

    logfunc create() {
        const auto log_target = []() -> std::string {
            const char *logs_target = getenv("LOGGI_TARGET");
            if (logs_target == nullptr) {
                return directly_invoked_by_systemd() ? "journal" : "stderr";
            } else {
                return logs_target;
            }
        }();
        if (log_target == "stdout") {
            return createStreamLogger(stdout);
        } else if (log_target == "stderr") {
            return createStreamLogger(stderr);
        } else if (log_target == "journal") {
            return createJournalLogger();
        } else if (log_target == "null") {
            return createNullLogger();
        } else {
            throw std::runtime_error(slog_fmt_ns::format("unknown log target: {}", log_target));
        }
    }
}

namespace loggi::impl {
    void log(const Opaque &opaque, level lvl, const std::string &str) {
        static logfunc instance = create();
        instance(opaque, lvl, str);
    }
}
