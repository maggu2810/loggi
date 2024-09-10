//
// Created by maggu2810 on 8/9/24.
//

#include <loggi/backend_sd.hxx>

#include <loggi/compat_fmt.hxx>

#include <vector>
#include <sstream>
#include <thread>
#include <functional>

#include <sys/uio.h>

#define SD_JOURNAL_SUPPRESS_LOCATION
#include <systemd/sd-journal.h>

namespace loggi::backend::sd {
    void log(::loggi::sloc sloc, ::loggi::level lvl, const std::string &str) {
        std::vector<std::string> entries;

        entries.push_back(::loggi::fmt::format("MESSAGE={}", str));
        entries.push_back(::loggi::fmt::format("PRIORITY={}", syslogLevel(lvl)));
        // thread ID
        {
            std::stringstream ss;
            ss << "TID=";
            ss << std::this_thread::get_id();
            entries.push_back(ss.str());
        }

        const auto call_sd_journal = [](std::vector<std::string> &entries,
                                        const std::function<int(const struct iovec *iov, int n)> &iovec_func) ->
            int {
            int iovcnt = static_cast<int>(entries.size());
            struct iovec iov[iovcnt];
            for (int i = 0; i < iovcnt; ++i) {
                iov[i].iov_base = entries[i].data();
                iov[i].iov_len = entries[i].length();
            }
            return iovec_func(iov, iovcnt);
        };

        int err;
        if (!::loggi::sloc_empty(sloc)) {
            entries.push_back(::loggi::fmt::format("CODE_COLUMN={}", sloc.column()));
            err = call_sd_journal(entries, [&](const struct iovec *iov, int n) {
                return sd_journal_sendv_with_location(
                    ::loggi::fmt::format("CODE_FILE={}", sloc.file_name()).data(),
                    ::loggi::fmt::format("CODE_LINE={}", sloc.line()).data(),
                    sloc.function_name(), iov, n);
            });
        } else {
            err = call_sd_journal(entries, [&](const struct iovec *iov, int n) {
                return sd_journal_sendv(iov, n);
            });
        }

        if (err) {
            const int errno_last = errno;
            std::fprintf(stderr, "send to sd_journal failed: err: %d, errno: %d\n", err, errno_last);
        }
    };
}
