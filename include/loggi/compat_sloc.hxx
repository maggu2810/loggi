//
// Created by maggu2810 on 8/7/24.
//

#ifndef LOGGI_COMPAT_SLOC_HXX
#define LOGGI_COMPAT_SLOC_HXX

#define SLOC_IMPL_SLOC_ENABLED 1

#if SLOG_IMPL_STD_SLOC
#include <source_location>

#define LOGGI_SLOC_CONSTR loggi::sloc{}

#if SLOC_IMPL_SLOC_ENABLED
#define LOGGI_IMPL_SLOC_C std::source_location::current()
#else
#define LOGGI_IMPL_SLOC_C {}
#endif

namespace loggi {
    class sloc : public std::source_location {
    public:
        sloc(const std::source_location sloc = LOGGI_IMPL_SLOC_C) // NOLINT(*-explicit-constructor)
            : std::source_location(sloc) {
        }
    };
}

#undef LOGGI_IMPL_SLOC_C

#else
#include <cstdint>
#include <string>

#if SLOC_IMPL_SLOC_ENABLED
#define LOGGI_SLOC_CONSTR loggi::sloc(__LINE__ , 0u, __FILE__, __PRETTY_FUNCTION__)
#else
#define LOGGI_SLOC_CONSTR { 0u, 0u, "", ""}
#endif

namespace loggi {
    class sloc {
    public:
        sloc(int line, std::uint_least32_t column, const char *file_name,
             const char *function_name) : m_line(line), m_column(column), m_file_name(file_name),
                                          m_function_name(function_name) {
        }

        sloc(std::uint_least32_t line, std::uint_least32_t column, const char *file_name,
             const char *function_name) : m_line(line), m_column(column), m_file_name(file_name),
                                          m_function_name(function_name) {
        }

        [[nodiscard]] std::uint_least32_t line() const noexcept { return m_line; }

        [[nodiscard]] uint_least32_t
        column() const noexcept { return m_column; }

        [[nodiscard]] const char *
        file_name() const noexcept { return m_file_name.data(); }

        [[nodiscard]] const char *
        function_name() const noexcept { return m_function_name.data(); }

    private:
        const uint_least32_t m_line;
        const uint_least32_t m_column;
        const std::string m_file_name;
        const std::string m_function_name;
    };
}
#endif

#include <cstring>

namespace loggi {
    inline bool sloc_empty(loggi::sloc sloc) {
        return sloc.line() == 0 && sloc.column() == 0 && strlen(sloc.file_name()) == 0 && strlen(
                   sloc.function_name()) == 0;
    }
}

#endif //LOGGI_COMPAT_SLOC_HXX
