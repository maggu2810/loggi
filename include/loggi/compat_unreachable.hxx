//
// Created by maggu2810 on 8/7/24.
//

#ifndef LOGGI_COMPAT_UNREACHABLE_HXX
#define LOGGI_COMPAT_UNREACHABLE_HXX

#if SLOC_IMPL_STD_UNREACHABLE
#include <utility>
#define LOGGI_UNREACHABLE std::unreachable
#else
[[noreturn,__gnu__::__always_inline__]]
inline void
LOGGI_UNREACHABLE() {
#ifdef _GLIBCXX_DEBUG
    std::__glibcxx_assert_fail(nullptr, 0, "std::unreachable()", nullptr);
#elif defined _GLIBCXX_ASSERTIONS
    __builtin_trap();
#else
    __builtin_unreachable();
#endif
}
#endif

#endif //LOGGI_COMPAT_UNREACHABLE_HXX
