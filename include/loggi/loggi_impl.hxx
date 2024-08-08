//
// Created by maggu2810 on 8/5/24.
//

#ifndef CPP_PLAYGROUND_LOGGING_IMPL_HXX
#define CPP_PLAYGROUND_LOGGING_IMPL_HXX

#include "loggi_compat_fmt.hxx"
#include "loggi_compat_sloc.hxx"

#include <thread>
#include <optional>

#include "level.hxx"

namespace loggi::impl {
    class Opaque {
    public:
        constexpr Opaque(std::optional<loggi::sloc> &&sloc LOGGI_SLOC_OPT_DFL_CONSTR, // NOLINT(*-explicit-constructor)
                         std::optional<std::thread::id> &&tid = {
#if LOGGING_IMPL_TID_ENABLED
                             std::this_thread::get_id()
#endif
                         }) : m_sloc(sloc), m_tid(tid) {
        }

        [[nodiscard]] constexpr const std::optional<loggi::sloc> &sloc() const { return m_sloc; };

        [[nodiscard]] constexpr const std::optional<std::thread::id> &tid() const { return m_tid; };

    private:
        const std::optional<loggi::sloc> m_sloc;
        const std::optional<std::thread::id> m_tid;
    };

    void log(const impl::Opaque &opaque, level lvl, const std::string &str);

    template<class... Args>
    constexpr void log(const impl::Opaque &opaque, level lvl, slog_fmt_ns::format_string<Args...> fmt,
                       Args &&... args) {
        log(opaque, lvl, slog_fmt_ns::format(fmt, std::forward<Args>(args)...));
    }
}

#define LOGGI_OPAQUE loggi::impl::Opaque(LOGGI_SLOC_CONSTR)

#endif //CPP_PLAYGROUND_LOGGING_IMPL_HXX
