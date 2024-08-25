//
// Created by maggu2810 on 8/19/24.
//

#ifndef LOGGI_PRINTF_LOGGI_HXX
#define LOGGI_PRINTF_LOGGI_HXX

#include "printf_backend.hxx"

#include "compat_fmt.hxx"
#include "compat_sloc.hxx"
#include "level.hxx"

#include <cstdarg>

#define LOGGI_PRINTF_LOG(...) ::loggi::printf::log(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_EMERG(...) ::loggi::printf::emerg(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_ALERT(...) ::loggi::printf::alert(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_CRIT(...) ::loggi::printf::crit(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_ERR(...) ::loggi::printf::err(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_WARN(...) ::loggi::printf::warn(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_NOTICE(...) ::loggi::printf::notice(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_INFO(...) ::loggi::printf::info(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_PRINTF_DEBUG(...) ::loggi::printf::debug(LOGGI_SLOC_CONSTR, __VA_ARGS__)

#define LOGGI_PRINTF_CALL_BACKEND_LOG(level) \
    do { \
        va_list ap;\
        va_start(ap, fmt);\
        try {\
            ::loggi::printf::backend::log(sloc, level, fmt, ap);\
            va_end(ap);\
        } catch (...) { \
            va_end(ap); \
        }\
    } while(0)

namespace loggi::printf {
    __attribute__((format(printf, 3, 4)))
    constexpr void log(::loggi::sloc sloc, level lvl, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(lvl);
    }

    __attribute__((format(printf, 2, 3)))
    constexpr void emerg(::loggi::sloc sloc, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::emergency);
    }

    __attribute__((format(printf, 2, 3)))
    constexpr void alert(::loggi::sloc sloc, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::alert);
    }

    __attribute__((format(printf, 2, 3)))
    constexpr void crit(::loggi::sloc sloc, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::critical);
    }

    __attribute__((format(printf, 2, 3)))
    constexpr void err(::loggi::sloc sloc, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::error);
    }

    __attribute__((format(printf, 2, 3)))
    constexpr void warn(::loggi::sloc sloc, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::warning);
    }

    __attribute__((format(printf, 2, 3)))
    constexpr void notice(::loggi::sloc sloc, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::notice);
    }

    __attribute__((format(printf, 2, 3)))
    constexpr void info(::loggi::sloc sloc, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::info);
    }

    __attribute__((format(printf, 2, 3)))
    constexpr void debug(::loggi::sloc sloc, const char *fmt, ...) {
        LOGGI_PRINTF_CALL_BACKEND_LOG(level::debug);
    }
}

#endif //LOGGI_PRINTF_LOGGI_HXX
