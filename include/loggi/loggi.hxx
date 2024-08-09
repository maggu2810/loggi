//
// Created by maggu2810 on 8/5/24.
//

#ifndef LOGGI_LOGGI_HXX
#define LOGGI_LOGGI_HXX

#ifndef LOGGI_BACKEND
#error LOGGI_BACKEND must be set
#endif
#define LOGGI_BACKEND_NS_AS_DFL 1
#if LOGGI_BACKEND == 0
#include "backend_dynamic.hxx"
#elif LOGGI_BACKEND == 1
#include "backend_stdout.hxx"
#elif LOGGI_BACKEND == 2
#include "backend_stderr.hxx"
#elif LOGGI_BACKEND == 3
#include "backend_sd.hxx"
#else
#error LOGGI_BACKEND not set
#endif
#undef LOGGI_BACKEND_NS_AS_DFL

#include "backend.hxx"

#include "compat_fmt.hxx"
#include "compat_sloc.hxx"
#include "level.hxx"

#define LOGGI_LOG(...) loggi::log(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_EMERG(...) loggi::emerg(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_ALERT(...) loggi::alert(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_CRIT(...) loggi::crit(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_ERR(...) loggi::err(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_WARN(...) loggi::warn(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_NOTICE(...) loggi::notice(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_INFO(...) loggi::info(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_DEBUG(...) loggi::debug(LOGGI_SLOC_CONSTR, __VA_ARGS__)

namespace loggi {
    template<class... Args>
    constexpr void log(::loggi::sloc sloc, level lvl, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::backend::log(sloc, lvl, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void emerg(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::backend::log(sloc, level::emergency, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void alert(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::backend::log(sloc, level::alert, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void crit(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::backend::log(sloc, level::critical, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void err(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::backend::log(sloc, level::error, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void warn(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::backend::log(sloc, level::warning, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void notice(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::backend::log(sloc, level::notice, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void info(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::backend::log(sloc, level::info, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void debug(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::backend::log(sloc, level::debug, fmt, std::forward<Args>(args)...);
    }
}

#endif //LOGGI_LOGGI_HXX
