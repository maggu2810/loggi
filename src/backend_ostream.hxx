//
// Created by maggu2810 on 8/9/24.
//

#ifndef BACKEND_OSTREAM_HXX
#define BACKEND_OSTREAM_HXX

#include <loggi/impl/sloc.hxx>
#include <loggi/level.hxx>
#include <loggi/impl/fmt.hxx>

#include <string>
#include <ostream>
#include <filesystem>

namespace loggi::backend::ostream {
    inline void log(std::ostream &os, ::loggi::context ctx, ::loggi::level lvl, const std::string &str) {
        const auto &sloc = ctx.sloc();
        os << format("[{}{}] {}\n", syslogLevel(lvl), sloc_empty(sloc)
                                                          ? ""
                                                          : format(",{}:{}:{}",
                                                                   std::filesystem::path(sloc.file_name()).
                                                                   filename().
                                                                   generic_string(), sloc.line(),
                                                                   sloc.column()),
                     str);
    }
}

#endif //BACKEND_OSTREAM_HXX
