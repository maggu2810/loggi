//
// Created by maggu2810 on 8/5/24.
//

#ifndef CPP_PLAYGROUND_LOGGING_HXX
#define CPP_PLAYGROUND_LOGGING_HXX

#include "loggi_compat_fmt.hxx"
#include "loggi_impl.hxx"

#define LOGGI_LOG(...) loggi::log(LOGGI_OPAQUE, __VA_ARGS__)
#define LOGGI_EMERG(...) loggi::emerg(LOGGI_OPAQUE, __VA_ARGS__)
#define LOGGI_ALERT(...) loggi::alert(LOGGI_OPAQUE, __VA_ARGS__)
#define LOGGI_CRIT(...) loggi::crit(LOGGI_OPAQUE, __VA_ARGS__)
#define LOGGI_ERR(...) loggi::err(LOGGI_OPAQUE, __VA_ARGS__)
#define LOGGI_WARN(...) loggi::warn(LOGGI_OPAQUE, __VA_ARGS__)
#define LOGGI_NOTICE(...) loggi::notice(LOGGI_OPAQUE, __VA_ARGS__)
#define LOGGI_INFO(...) loggi::info(LOGGI_OPAQUE, __VA_ARGS__)
#define LOGGI_DEBUG(...) loggi::debug(LOGGI_OPAQUE, __VA_ARGS__)

namespace loggi {
    template<class... Args>
    constexpr void log(impl::Opaque opaque, level lvl, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        impl::log(opaque, lvl, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void emerg(impl::Opaque opaque, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        impl::log(opaque, level::emergency, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void alert(impl::Opaque opaque, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        impl::log(opaque, level::alert, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void crit(impl::Opaque opaque, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        impl::log(opaque, level::critical, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void err(impl::Opaque opaque, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        impl::log(opaque, level::error, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void warn(impl::Opaque opaque, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        impl::log(opaque, level::warning, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void notice(impl::Opaque opaque, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        impl::log(opaque, level::notice, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void info(impl::Opaque opaque, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        impl::log(opaque, level::info, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void debug(impl::Opaque opaque, slog_fmt_ns::format_string<Args...> fmt, Args &&... args) {
        impl::log(opaque, level::debug, fmt, std::forward<Args>(args)...);
    }
}

#endif //CPP_PLAYGROUND_LOGGING_HXX
