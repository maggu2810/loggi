//
// Created by maggu2810 on 8/19/24.
//

#ifndef LOGGI_LOGGI_HXX
#define LOGGI_LOGGI_HXX

#define LOGGI_LOG(...) loggi::log(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_EMERG(...) loggi::emerg(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_ALERT(...) loggi::alert(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_CRIT(...) loggi::crit(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_ERR(...) loggi::err(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_WARN(...) loggi::warn(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_NOTICE(...) loggi::notice(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_INFO(...) loggi::info(LOGGI_SLOC_CONSTR, __VA_ARGS__)
#define LOGGI_DEBUG(...) loggi::debug(LOGGI_SLOC_CONSTR, __VA_ARGS__)

#ifndef LOGGI_BACKEND
#define LOGGI_BACKEND 0
#endif

#ifdef LOGGI_BACKEND
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
#endif //LOGGI_BACKEND

#ifndef LOGGI_FRONTEND
#define LOGGI_FRONTEND 0
#endif

#ifdef LOGGI_FRONTEND
#define LOGGI_FRONTEND_SET_DFL(type) namespace loggi { using loggi::type::log; using loggi::type::emerg; using loggi::type::alert; using loggi::type::crit; using loggi::type::err; using loggi::type::warn; using loggi::type::notice; using loggi::type::info; using loggi::type::debug;  }
#if LOGGI_FRONTEND == 0
#include "format_loggi.hxx"
LOGGI_FRONTEND_SET_DFL(format)
#elif LOGGI_FRONTEND == 1
#include "printf_loggi.hxx"
LOGGI_FRONTEND_SET_DFL(printf)
#endif
#endif

#endif //LOGGI_LOGGI_HXX
