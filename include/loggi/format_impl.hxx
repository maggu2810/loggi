//
// Created by maggu2810 on 8/19/24.
//

#ifndef LOGGI_FORMAT_IMPL_HXX
#define LOGGI_FORMAT_IMPL_HXX

#include "backend.hxx"
#include "compat_fmt.hxx"
#include "compat_sloc.hxx"

#include "level.hxx"

namespace loggi::format::impl {
    template<class... Args>
    constexpr void log(::loggi::sloc sloc, ::loggi::level lvl, ::loggi::fmt::format_string<Args...> fmt,
                       Args &&... args) {
        ::loggi::backend::log(sloc, lvl, ::loggi::fmt::format(fmt, std::forward<Args>(args)...));
    }
}

#endif //LOGGI_FORMAT_IMPL_HXX
