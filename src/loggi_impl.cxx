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
#include <thread>

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

    using logfunc = std::function<void(loggi::sloc sloc, loggi::level lvl,
                                       const std::string &str)>;

    logfunc createStreamLogger(FILE *stream) {
        return [stream](loggi::sloc sloc, loggi::level lvl, const std::string &str) -> void {
            std::stringstream ss;
            if (!sloc_empty(sloc)) {
                ss << "[" << std::filesystem::path(sloc.file_name()).filename().generic_string() << ":" << sloc.line()
                        << ":" << sloc.column() << "] ";
            }
            ss << "level: " << static_cast<int>(lvl) << " => " << str << "\n";
            std::fprintf(stream, "%s", ss.str().data());
        };
    }

    logfunc createJournalLogger() {
        return [](loggi::sloc sloc, loggi::level lvl, const std::string &str) -> void {
            std::vector<std::string> entries;

            entries.push_back(slog_fmt_ns::format("MESSAGE={}", str));
            entries.push_back(slog_fmt_ns::format("PRIORITY={}", syslogLevel(lvl)));
            // thread ID
            {
                std::stringstream ss;
                ss << "TID=";
                ss << std::this_thread::get_id();
                entries.push_back(ss.str());
            }

            int iovcnt = static_cast<int>(entries.size());
            struct iovec iov[iovcnt];
            for (int i = 0; i < iovcnt; ++i) {
                iov[i].iov_base = entries[i].data();
                iov[i].iov_len = entries[i].length();
            }

            int err;
            if (!loggi::sloc_empty(sloc)) {
                err = sd_journal_sendv_with_location(
                    slog_fmt_ns::format("CODE_FILE={}", sloc.file_name()).data(),
                    slog_fmt_ns::format("CODE_LINE={}", sloc.line()).data(),
                    sloc.function_name(), iov, iovcnt);
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
        return [](loggi::sloc sloc, loggi::level lvl, const std::string &str) -> void {
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
    void log(loggi::sloc sloc, level lvl, const std::string &str) {
        static logfunc instance = create();
        instance(sloc, lvl, str);
    }
}
