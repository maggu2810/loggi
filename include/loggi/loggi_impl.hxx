//
// Created by maggu2810 on 8/5/24.
//

#ifndef CPP_PLAYGROUND_LOGGING_IMPL_HXX
#define CPP_PLAYGROUND_LOGGING_IMPL_HXX

#include "loggi_compat_fmt.hxx"
#include "loggi_compat_sloc.hxx"

#include "level.hxx"

namespace loggi::impl {
    void log(loggi::sloc sloc, level lvl, const std::string &str);

    template<class... Args>
    constexpr void log(loggi::sloc sloc, level lvl, slog_fmt_ns::format_string<Args...> fmt,
                       Args &&... args) {
        log(sloc, lvl, slog_fmt_ns::format(fmt, std::forward<Args>(args)...));
    }
}

#endif //CPP_PLAYGROUND_LOGGING_IMPL_HXX
