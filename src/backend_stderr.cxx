//
// Created by maggu2810 on 8/9/24.
//

#include <loggi/backend/backend_stderr.hxx>

#include "backend_ostream.hxx"

#include <iostream>

namespace loggi::backend::stderr {
    void log(const ::loggi::context& ctx, ::loggi::level lvl, const std::string &str) {
        ::loggi::backend::ostream::log(std::cerr, ctx, lvl, str);
    }
}
