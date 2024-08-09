//
// Created by maggu2810 on 8/9/24.
//

#include <loggi/backend_stderr.hxx>

#include "backend_ostream.hxx"

#include <iostream>

namespace loggi::backend::stderr {
    void log(loggi::sloc sloc, level lvl, const std::string &str) {
        loggi::backend::ostream::log(std::cerr, sloc, lvl, str);
    }
}