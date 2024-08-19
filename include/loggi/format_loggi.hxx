//
// Created by maggu2810 on 8/5/24.
//

#ifndef LOGGI_FORMAT_LOGGI_HXX
#define LOGGI_FORMAT_LOGGI_HXX

#include "format_backend.hxx"

#include "compat_fmt.hxx"
#include "compat_sloc.hxx"
#include "level.hxx"

namespace loggi::format {
    template<class... Args>
    constexpr void log(::loggi::sloc sloc, level lvl, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::backend::log(sloc, lvl, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void emerg(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::backend::log(sloc, level::emergency, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void alert(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::backend::log(sloc, level::alert, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void crit(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::backend::log(sloc, level::critical, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void err(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::backend::log(sloc, level::error, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void warn(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::backend::log(sloc, level::warning, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void notice(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::backend::log(sloc, level::notice, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void info(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::backend::log(sloc, level::info, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void debug(::loggi::sloc sloc, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::backend::log(sloc, level::debug, fmt, std::forward<Args>(args)...);
    }
}

#endif //LOGGI_FORMAT_LOGGI_HXX
