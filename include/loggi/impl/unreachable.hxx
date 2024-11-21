//
// Created by maggu2810 on 8/7/24.
//

#ifndef LOGGI_IMPL_UNREACHABLE_HXX
#define LOGGI_IMPL_UNREACHABLE_HXX

#include <version>

#if __cpp_lib_unreachable >= 202202L

#include <utility>

namespace loggi_impl {
    using std::unreachable;
}

#else

namespace loggi_impl {
    [[noreturn,__gnu__::__always_inline__]]
    inline void
    unreachable() {
#ifdef _GLIBCXX_DEBUG
        std::__glibcxx_assert_fail(nullptr, 0, "std::unreachable()", nullptr);
#elif defined _GLIBCXX_ASSERTIONS
        __builtin_trap();
#else
        __builtin_unreachable();
#endif
    }
}

#endif

#endif //LOGGI_IMPL_UNREACHABLE_HXX
