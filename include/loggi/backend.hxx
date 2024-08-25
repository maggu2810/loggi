//
// Created by maggu2810 on 8/9/24.
//

#ifndef LOGGI_BACKEND_HXX
#define LOGGI_BACKEND_HXX

#include "compat_sloc.hxx"
#include "level.hxx"
#include <string>

#ifndef LOGGI_BACKEND
#define LOGGI_BACKEND 0
#endif

#ifndef LOGGI_BACKEND_NS_AS_DFL
#define LOGGI_BACKEND_NS_AS_DFL 1
#endif //LOGGI_BACKEND_NS_AS_DFL

#if LOGGI_BACKEND_NS_AS_DFL

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

#if 1
namespace loggi::backend {
    inline void log(::loggi::sloc sloc, ::loggi::level lvl, const std::string &str) {
        LOGGI_BACKEND_NS::log(sloc, lvl, str);
    }
}
#else
namespace loggi::backend {
    using LOGGI_BACKEND_NS::log;
}
#endif

#else
namespace loggi::backend {
    void log(::loggi::sloc sloc, ::loggi::level lvl, const std::string &str);
}
#endif

#endif //LOGGI_BACKEND_HXX
