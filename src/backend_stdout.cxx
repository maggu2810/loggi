//
// Created by maggu2810 on 8/9/24.
//

#include <loggi/backend/backend_stdout.hxx>

#include "backend_ostream.hxx"

#include <iostream>

namespace loggi::backend::stdout {
    void log(const ::loggi::context& ctx, ::loggi::level lvl, const std::string &str) {
        ::loggi::backend::ostream::log(std::cout, ctx, lvl, str);
    }
}
