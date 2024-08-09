//
// Created by maggu2810 on 8/5/24.
//

#ifndef LOGGI_LEVEL_HXX
#define LOGGI_LEVEL_HXX

#include <sys/syslog.h>
#include <loggi/compat_unreachable.hxx>

namespace loggi {
    enum class level {
        emergency, alert, critical, error, warning, notice, info, debug
    };

    inline int syslogLevel(loggi::level level) {
        switch (level) {
            case loggi::level::emergency:
                return LOG_EMERG;
            case loggi::level::alert:
                return LOG_ALERT;
            case loggi::level::critical:
                return LOG_CRIT;
            case loggi::level::error:
                return LOG_ERR;
            case loggi::level::warning:
                return LOG_WARNING;
            case loggi::level::notice:
                return LOG_NOTICE;
            case loggi::level::info:
                return LOG_INFO;
            case loggi::level::debug:
                return LOG_DEBUG;
        }
        LOGGI_UNREACHABLE();
    }
}

#endif //LOGGI_LEVEL_HXX
