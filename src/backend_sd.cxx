//
// Created by maggu2810 on 8/9/24.
//

#include <loggi/backend/backend_sd.hxx>

#include <loggi/impl/fmt.hxx>

#include <vector>
#include <sstream>
#include <thread>
#include <functional>

#include <sys/uio.h>

#define SD_JOURNAL_SUPPRESS_LOCATION
#include <systemd/sd-journal.h>

namespace loggi::backend::sd {
    void log(const ::loggi::context& ctx, ::loggi::level lvl, const std::string &str) {
        std::vector<std::string> entries;

        entries.push_back(::loggi_impl::fmt::format("MESSAGE={}", str));
        entries.push_back(::loggi_impl::fmt::format("PRIORITY={}", syslogLevel(lvl)));
        entries.push_back(::loggi_impl::fmt::format("TID={}", ctx.tid()));

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
        const auto& sloc = ctx.sloc();
        if (!::loggi_impl::sloc_empty(sloc)) {
            entries.push_back(::loggi_impl::fmt::format("CODE_COLUMN={}", sloc.column()));
            err = call_sd_journal(entries, [&](const struct iovec *iov, int n) {
                return sd_journal_sendv_with_location(
                    ::loggi_impl::fmt::format("CODE_FILE={}", sloc.file_name()).data(),
                    ::loggi_impl::fmt::format("CODE_LINE={}", sloc.line()).data(),
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
