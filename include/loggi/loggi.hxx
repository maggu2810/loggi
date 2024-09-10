//
// Created by maggu2810 on 8/19/24.
//

#ifndef LOGGI_LOGGI_HXX
#define LOGGI_LOGGI_HXX

// set the default loggi frontend if not set by user
#ifndef LOGGI_FRONTEND
#define LOGGI_FRONTEND 0
#endif

#ifndef LOGGI_FRONTEND_SHORTCUT
#define LOGGI_FRONTEND_SHORTCUT 1
#endif

#if LOGGI_FRONTEND_SHORTCUT
#define LOGGI_LOG(...) ::loggi::log(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_EMERG(...) ::loggi::emerg(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_ALERT(...) ::loggi::alert(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_CRIT(...) ::loggi::crit(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_ERR(...) ::loggi::err(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_WARN(...) ::loggi::warn(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_NOTICE(...) ::loggi::notice(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_INFO(...) ::loggi::info(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_DEBUG(...) ::loggi::debug(LOGGI_SLOC_CONSTR, __VA_ARGS__)

#define LOGGI_FRONTEND_SET_DFL_TYPE(type) namespace loggi { using ::loggi::type::log; using ::loggi::type::emerg; using ::loggi::type::alert; using ::loggi::type::crit; using ::loggi::type::err; using ::loggi::type::warn; using ::loggi::type::notice; using ::loggi::type::info; using ::loggi::type::debug;  }
#else
#define LOGGI_FRONTEND_SET_DFL_TYPE(type)
#endif

#if LOGGI_FRONTEND == 0
#include "loggi_format.hxx"
LOGGI_FRONTEND_SET_DFL_TYPE(format)
#elif LOGGI_FRONTEND == 1
#include "loggi_printf.hxx"
LOGGI_FRONTEND_SET_DFL_TYPE(printf)
#endif

#endif //LOGGI_LOGGI_HXX
