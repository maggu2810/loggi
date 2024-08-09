//
// Created by maggu2810 on 8/9/24.
//

#ifndef LOGGI_BACKEND_HDRGEN_HXX
#define LOGGI_BACKEND_HDRGEN_HXX

#include "compat_sloc.hxx"
#include "level.hxx"

#include <string>

#endif //LOGGI_BACKEND_HDRGEN_HXX

#ifdef LOGGI_BACKEND_NS
namespace LOGGI_BACKEND_NS {
    void log(loggi::sloc sloc, level lvl, const std::string &str);
}
#ifdef LOGGI_BACKEND_NS_AS_DFL
namespace loggi::backend { inline void log(loggi::sloc sloc, level lvl, const std::string &str) { LOGGI_BACKEND_NS::log(sloc, lvl ,str); } }
#endif
#endif
