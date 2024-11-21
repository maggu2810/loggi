//
// Created by maggu2810 on 8/19/24.
//

#ifndef LOGGI_PRINTF_LOGGI_HXX
#define LOGGI_PRINTF_LOGGI_HXX

#include <loggi/impl/printf.hxx>

#include <loggi/context.hxx>
#include <loggi/impl/fmt.hxx>
#include <loggi/impl/constexpr.hxx>
#include <loggi/level.hxx>

#include <cstdarg>

#define LOGGI_PRINTF_LOG(...) ::loggi::printf::log(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_EMERG(...) ::loggi::printf::emerg(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_ALERT(...) ::loggi::printf::alert(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_CRIT(...) ::loggi::printf::crit(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_ERR(...) ::loggi::printf::err(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_WARN(...) ::loggi::printf::warn(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_NOTICE(...) ::loggi::printf::notice(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_INFO(...) ::loggi::printf::info(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_DEBUG(...) ::loggi::printf::debug(LOGGI_CONTEXT_CONSTR, __VA_ARGS__)

#define LOGGI_PRINTF_CALL_BACKEND_LOG(level) \
    do { \
        va_list ap;\
        va_start(ap, fmt);\
        ::loggi_impl::printf::vaend_on_destruction vaend(ap);\
        ::loggi_impl::printf::log(ctx, level, fmt, ap);\
    } while(0)

namespace loggi::printf {
    __attribute__((format(printf, 3, 4)))
    LOGGI_IMPL_CONSTEXPR_GE23 void log(const ::loggi::context &ctx, ::loggi::level lvl, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(lvl);
    }

    __attribute__((format(printf, 2, 3)))
    LOGGI_IMPL_CONSTEXPR_GE23 void emerg(const ::loggi::context &ctx, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::emergency);
    }

    __attribute__((format(printf, 2, 3)))
    LOGGI_IMPL_CONSTEXPR_GE23 void alert(const ::loggi::context &ctx, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::alert);
    }

    __attribute__((format(printf, 2, 3)))
    LOGGI_IMPL_CONSTEXPR_GE23 void crit(const ::loggi::context &ctx, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::critical);
    }

    __attribute__((format(printf, 2, 3)))
    LOGGI_IMPL_CONSTEXPR_GE23 void err(const ::loggi::context &ctx, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::error);
    }

    __attribute__((format(printf, 2, 3)))
    LOGGI_IMPL_CONSTEXPR_GE23 void warn(const ::loggi::context &ctx, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::warning);
    }

    __attribute__((format(printf, 2, 3)))
    LOGGI_IMPL_CONSTEXPR_GE23 void notice(const ::loggi::context &ctx, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::notice);
    }

    __attribute__((format(printf, 2, 3)))
    LOGGI_IMPL_CONSTEXPR_GE23 void info(const ::loggi::context &ctx, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::info);
    }

    __attribute__((format(printf, 2, 3)))
    LOGGI_IMPL_CONSTEXPR_GE23 void debug(const ::loggi::context &ctx, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::debug);
    }
}

#endif //LOGGI_PRINTF_LOGGI_HXX
