//
// Created by maggu2810 on 8/9/24.
//

#ifndef LOGGI_BACKEND_HXX
#define LOGGI_BACKEND_HXX

#include <loggi/context.hxx>
#include <loggi/level.hxx>
#include <string>

#ifdef LOGGI_BACKEND
#if LOGGI_BACKEND == 0
#include "backend_dynamic.hxx"
#elif LOGGI_BACKEND == 1
#include "backend_stdout.hxx"
#elif LOGGI_BACKEND == 2
#include "backend_stderr.hxx"
#elif LOGGI_BACKEND == 3
#include "backend_sd.hxx"
#else
#error LOGGI_BACKEND value not known
#endif

#if 0
namespace loggi::backend {
    inline void log(const ::loggi::context& ctx, ::loggi::level lvl, const std::string &str) {
        LOGGI_BACKEND_NS::log(ctx, lvl, str);
    }
}
#else
namespace loggi::backend {
    using LOGGI_BACKEND_NS::log;
}
#endif

#else
namespace loggi::backend {
    void log(const ::loggi::context &ctx, ::loggi::level lvl, const std::string &str);
}
#endif

#endif //LOGGI_BACKEND_HXX
