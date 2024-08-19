//
// Created by maggu2810 on 8/9/24.
//

#ifndef LOGGI_BACKEND_HXX
#define LOGGI_BACKEND_HXX

#include "compat_sloc.hxx"
#include "level.hxx"
#include <string>

namespace loggi::backend {
    void log(::loggi::sloc sloc, ::loggi::level lvl, const std::string &str);
}

#endif //LOGGI_BACKEND_HXX
