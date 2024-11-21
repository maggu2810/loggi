//
// Created by maggu2810 on 8/5/24.
//

#ifndef LOGGI_FORMAT_LOGGI_HXX
#define LOGGI_FORMAT_LOGGI_HXX

#include <loggi/impl/format.hxx>
#include <loggi/impl/fmt.hxx>
#include <loggi/context.hxx>
#include <loggi/level.hxx>

#define LOGGI_FORMAT_LOG(...) ::loggi::format::log(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_EMERG(...) ::loggi::format::emerg(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_ALERT(...) ::loggi::format::alert(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_CRIT(...) ::loggi::format::crit(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_ERR(...) ::loggi::format::err(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_WARN(...) ::loggi::format::warn(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_NOTICE(...) ::loggi::format::notice(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_INFO(...) ::loggi::format::info(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_FORMAT_DEBUG(...) ::loggi::format::debug(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)

namespace loggi::format {
    template<class... Args>
    constexpr void log(const ::loggi::context &ctx, ::loggi::level lvl, ::loggi_impl::fmt::format_string<Args...> fmt,
                       Args &&... args) {
        ::loggi_impl::format::log(ctx, lvl, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void emerg(const ::loggi::context &ctx, ::loggi_impl::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi_impl::format::log(ctx, level::emergency, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void alert(const ::loggi::context &ctx, ::loggi_impl::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi_impl::format::log(ctx, level::alert, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void crit(const ::loggi::context &ctx, ::loggi_impl::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi_impl::format::log(ctx, level::critical, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void err(const ::loggi::context &ctx, ::loggi_impl::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi_impl::format::log(ctx, level::error, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void warn(const ::loggi::context &ctx, ::loggi_impl::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi_impl::format::log(ctx, level::warning, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void notice(const ::loggi::context &ctx, ::loggi_impl::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi_impl::format::log(ctx, level::notice, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void info(const ::loggi::context &ctx, ::loggi_impl::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi_impl::format::log(ctx, level::info, fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    constexpr void debug(const ::loggi::context &ctx, ::loggi_impl::fmt::format_string<Args...> fmt, Args &&... args) {
        ::loggi_impl::format::log(ctx, level::debug, fmt, std::forward<Args>(args)...);
    }
}

#endif //LOGGI_FORMAT_LOGGI_HXX
