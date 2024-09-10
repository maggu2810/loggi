//
// Created by maggu2810 on 8/19/24.
//

#ifndef LOGGI_PRINTF_IMPL_HXX
#define LOGGI_PRINTF_IMPL_HXX

#include "backend.hxx"
#include "compat_sloc.hxx"

#include "level.hxx"

#include <cstdio>
#include <memory>

namespace loggi::printf::impl {
    class vaend_on_destruction {
    public:
        explicit vaend_on_destruction(va_list &ap) : m_ap(ap) {
        }

        ~vaend_on_destruction() { va_end(m_ap); }

    private:
        va_list &m_ap;
    };

    constexpr void log(::loggi::sloc sloc, ::loggi::level lvl, const char *fmt, va_list ap) {
        char* buffer;
        if (const int rv = vasprintf(&buffer, fmt, ap); rv != -1) {
            std::unique_ptr<char *, void(*)(char **)> str(&buffer, [](char **ptr) {
                free(*ptr);
            });
            ::loggi::backend::log(sloc, lvl, buffer);
        }
    }
}

#endif //LOGGI_PRINTF_IMPL_HXX
