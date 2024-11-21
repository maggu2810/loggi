//
// Created by maggu2810 on 8/19/24.
//

#ifndef LOGGI_IMPL_FORMAT_HXX
#define LOGGI_IMPL_FORMAT_HXX

#include <loggi/backend/backend.hxx>
#include <loggi/impl/fmt.hxx>
#include <loggi/context.hxx>
#include <loggi/level.hxx>

namespace loggi_impl::format {
    template<class... Args>
    constexpr void log(const ::loggi::context& ctx, ::loggi::level lvl, ::loggi_impl::fmt::format_string<Args...> fmt,
                       Args &&... args) {
        ::loggi::backend::log(ctx, lvl, ::loggi_impl::fmt::format(fmt, std::forward<Args>(args)...));
    }
}

#endif //LOGGI_IMPL_FORMAT_HXX
