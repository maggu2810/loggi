//
// Created by maggu2810 on 8/9/24.
//

#ifndef LOGGI_BACKEND_HDRGEN_HXX
#define LOGGI_BACKEND_HDRGEN_HXX

#include <loggi/context.hxx>
#include <loggi/level.hxx>

#include <string>

#endif //LOGGI_BACKEND_HDRGEN_HXX

#ifdef LOGGI_BACKEND_NS
namespace
LOGGI_BACKEND_NS {
    void log(const ::loggi::context &ctx, ::loggi::level lvl, const std::string &str);
}
#endif
