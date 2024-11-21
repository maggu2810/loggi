//
// Created by maggu2810 on 9/19/24.
//

#ifndef LOGGI_IMPL_CONSTEXPR_HXX
#define LOGGI_IMPL_CONSTEXPR_HXX

#if __cplusplus < 202302L
#define LOGGI_IMPL_CONSTEXPR_GE23
#else
#define LOGGI_IMPL_CONSTEXPR_GE23 constexpr
#endif

#if __cplusplus < 202002L
#define LOGGI_IMPL_CONSTEXPR_GE20
#else
#define LOGGI_IMPL_CONSTEXPR_GE20 constexpr
#endif

#endif //LOGGI_IMPL_CONSTEXPR_HXX
