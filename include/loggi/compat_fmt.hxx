//
// Created by maggu2810 on 8/7/24.
//

#ifndef LOGGI_COMPAT_FMT_HXX
#define LOGGI_COMPAT_FMT_HXX

#if SLOG_IMPL_STD_FORMAT
#include <format>
namespace loggi::fmt {
    using ::std::format_string;
    using ::std::format;
}
#else
#include <fmt/format.h>
namespace loggi::fmt {
    using ::fmt::format_string;
    using ::fmt::format;
}
#endif

#endif //LOGGI_COMPAT_FMT_HXX
