//
// Created by maggu2810 on 8/5/24.
//

#ifndef LOGGI_FORMAT_LOGGI_HXX
#define LOGGI_FORMAT_LOGGI_HXX

#include "format_impl.hxx"

#include "compat_fmt.hxx"
#include "compat_sloc.hxx"
#include "level.hxx"

#define LOGGI_FORMAT_LOG(...) ::loggi::format::log(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_EMERG(...) ::loggi::format::emerg(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_ALERT(...) ::loggi::format::alert(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_CRIT(...) ::loggi::format::crit(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_ERR(...) ::loggi::format::err(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_WARN(...) ::loggi::format::warn(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_NOTICE(...) ::loggi::format::notice(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_INFO(...) ::loggi::format::info(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_DEBUG(...) ::loggi::format::debug(LOGGI_SLOC_CONSTR, __VA_ARGS__)

namespace loggi::format {
    template<class... Args>
    constexpr void log(::loggi::sloc sloc, ::loggi::level lvl, ::loggi::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::impl::log(sloc, lvl, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void emerg(::loggi::sloc sloc, ::loggi::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::impl::log(sloc, level::emergency, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void alert(::loggi::sloc sloc, ::loggi::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::impl::log(sloc, level::alert, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void crit(::loggi::sloc sloc, ::loggi::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::impl::log(sloc, level::critical, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void err(::loggi::sloc sloc, ::loggi::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::impl::log(sloc, level::error, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void warn(::loggi::sloc sloc, ::loggi::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::impl::log(sloc, level::warning, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void notice(::loggi::sloc sloc, ::loggi::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::impl::log(sloc, level::notice, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void info(::loggi::sloc sloc, ::loggi::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::impl::log(sloc, level::info, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void debug(::loggi::sloc sloc, ::loggi::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi::format::impl::log(sloc, level::debug, fmt, std::forward<Args>(args)...);
    }
}

#endif //LOGGI_FORMAT_LOGGI_HXX
