//
// Created by maggu2810 on 11/21/24.
//
#ifndef LOG_HXX
#define LOG_HXX

#include "loggi_format.hxx"
#include "loggi_printf.hxx"

#define LOGF(...) LOGGI_FORMAT_LOG(__VA_ARGS__)
#define LOGFU(...) LOGGI_FORMAT_EMERG(__VA_ARGS__)
#define LOGFA(...) LOGGI_FORMAT_ALERT(__VA_ARGS__)
#define LOGFC(...) LOGGI_FORMAT_CRIT(__VA_ARGS__)
#define LOGFE(...) LOGGI_FORMAT_ERR(__VA_ARGS__)
#define LOGFW(...) LOGGI_FORMAT_WARN(__VA_ARGS__)
#define LOGFN(...) LOGGI_FORMAT_NOTICE(__VA_ARGS__)
#define LOGFI(...) LOGGI_FORMAT_INFO(__VA_ARGS__)
#define LOGFD(...) LOGGI_FORMAT_DEBUG(__VA_ARGS__)
#define LOGP(...) LOGGI_PRINTF_LOG(__VA_ARGS__)
#define LOGPU(...) LOGGI_PRINTF_EMERG(__VA_ARGS__)
#define LOGPA(...) LOGGI_PRINTF_ALERT(__VA_ARGS__)
#define LOGPC(...) LOGGI_PRINTF_CRIT(__VA_ARGS__)
#define LOGPE(...) LOGGI_PRINTF_ERR(__VA_ARGS__)
#define LOGPW(...) LOGGI_PRINTF_WARN(__VA_ARGS__)
#define LOGPN(...) LOGGI_PRINTF_NOTICE(__VA_ARGS__)
#define LOGPI(...) LOGGI_PRINTF_INFO(__VA_ARGS__)
#define LOGPD(...) LOGGI_PRINTF_DEBUG(__VA_ARGS__)


#endif //LOG_HXX
