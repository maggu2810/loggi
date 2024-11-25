//
// Created by maggu2810 on 8/9/24.
//

#include <loggi/backend/backend_dynamic.hxx>

#include <loggi/backend/backend_sd.hxx>
#include <loggi/backend/backend_stderr.hxx>
#include <loggi/backend/backend_stdout.hxx>

#include <loggi/impl/fmt.hxx>

#include <unistd.h>
#include <functional>

namespace {
    bool directly_invoked_by_systemd() {
        const char *systemd_exec_pid = std::getenv("SYSTEMD_EXEC_PID");
        if (systemd_exec_pid == nullptr) {
            return ::getppid() == 1;
        } else {
            return std::to_string(::getpid()) == systemd_exec_pid;
        }
    }

    using logfunc = std::function<void(::loggi::context ctx, ::loggi::level lvl,
                                       const std::string &str)>;

    logfunc createNullLogger() {
        return [](::loggi::context ctx, ::loggi::level lvl, const std::string &str) -> void {
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
            return ::loggi::backend::stdout::log;
        } else if (log_target == "stderr") {
            return ::loggi::backend::stderr::log;
        } else if (log_target == "journal") {
            return ::loggi::backend::sd::log;
        } else if (log_target == "null") {
            return createNullLogger();
        } else {
            throw std::runtime_error(::loggi_impl::fmt::format("unknown log target: {}", log_target));
        }
    }
}

namespace loggi::backend::dynamic {
    void log(const ::loggi::context& ctx, ::loggi::level lvl, const std::string &str) {
        static logfunc instance = create();
        instance(ctx, lvl, str);
    }
}
