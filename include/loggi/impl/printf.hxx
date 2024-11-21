//
// Created by maggu2810 on 8/19/24.
//

#ifndef LOGGI_IMPL_PRINTF_HXX
#define LOGGI_IMPL_PRINTF_HXX

#include <loggi/backend/backend.hxx>
#include <loggi/impl/cod.hxx>
#include <loggi/impl/sloc.hxx>
#include <loggi/level.hxx>

#include <cstdio>
#include <memory>
#include <cstdarg>

namespace loggi_impl::printf {
    class vaend_on_destruction {
    public:
        constexpr explicit vaend_on_destruction(va_list &ap) : m_ap(ap) {
        }

        LOGGI_IMPL_CONSTEXPR_GE20 ~vaend_on_destruction() { va_end(m_ap); }

    private:
        va_list &m_ap;
    };

    LOGGI_IMPL_CONSTEXPR_GE23 void log(const ::loggi::context &ctx, ::loggi::level lvl, const char *fmt, va_list ap) {
        char *buffer;
        if (const int rv = vasprintf(&buffer, fmt, ap); rv != -1) {
            const cod_free free_buffer(buffer);
            ::loggi::backend::log(ctx, lvl, buffer);
        }
    }
}

#endif //LOGGI_IMPL_PRINTF_HXX
