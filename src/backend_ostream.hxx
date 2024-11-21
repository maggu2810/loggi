//
// Created by maggu2810 on 8/9/24.
//

#ifndef BACKEND_OSTREAM_HXX
#define BACKEND_OSTREAM_HXX

#include <loggi/impl/sloc.hxx>
#include <loggi/level.hxx>

#include <string>
#include <ostream>
#include <filesystem>

namespace loggi::backend::ostream {
    inline void log(std::ostream &os, ::loggi::context ctx, ::loggi::level lvl, const std::string &str) {
        const auto &sloc = ctx.sloc();
        if (!::loggi_impl::sloc_empty(sloc)) {
            os << "[" << std::filesystem::path(sloc.file_name()).filename().generic_string() << ":" << sloc.line()
                    << ":" << sloc.column() << "] ";
        }
        os << "level: " << static_cast<int>(lvl) << " => " << str << "\n";
    }
}

#endif //BACKEND_OSTREAM_HXX
