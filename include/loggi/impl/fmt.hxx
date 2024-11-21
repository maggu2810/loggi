//
// Created by maggu2810 on 8/7/24.
//

#ifndef LOGGI_IMPL_FMT_HXX
#define LOGGI_IMPL_FMT_HXX

#if LOGGI_IMPL_STD_FORMAT
#include <format>

namespace loggi_impl::fmt {
    using ::std::format_string;
    using ::std::format;
}
#else
#include <fmt/format.h>

namespace loggi_impl::fmt {
    using ::fmt::format_string;
    using ::fmt::format;
}
#endif

#endif //LOGGI_IMPL_FMT_HXX
