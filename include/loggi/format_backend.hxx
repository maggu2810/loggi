//
// Created by maggu2810 on 8/19/24.
//

#ifndef LOGGI_FORMAT_BACKEND_HXX
#define LOGGI_FORMAT_BACKEND_HXX

#include "backend.hxx"
#include "compat_fmt.hxx"
#include "compat_sloc.hxx"

#include "level.hxx"

namespace loggi::format::backend {
    template<class... Args>
    constexpr void log(loggi::sloc sloc, level lvl, slog_fmt_ns::format_string<Args...> fmt,
                       Args &&... args) {
        ::loggi::backend::log(sloc, lvl, slog_fmt_ns::format(fmt, std::forward<Args>(args)...));
    }
}

#endif //LOGGI_FORMAT_BACKEND_HXX
