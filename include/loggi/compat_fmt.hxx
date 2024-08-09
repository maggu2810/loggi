//
// Created by maggu2810 on 8/7/24.
//

#ifndef LOGGI_COMPAT_FMT_HXX
#define LOGGI_COMPAT_FMT_HXX

#if SLOG_IMPL_STD_FORMAT
#include <format>
#define slog_fmt_ns std
#else
#include <fmt/format.h>
#define slog_fmt_ns fmt
#endif

#endif //LOGGI_COMPAT_FMT_HXX
