//
// Created by maggu2810 on 8/7/24.
//

#ifndef LOGGI_SLOC_HXX
#define LOGGI_SLOC_HXX

#if SLOG_IMPL_STD_SLOC
#include <source_location>

#define LOGGI_SLOC_CONSTR std::source_location::current()
#define LOGGI_SLOC_OPT_DFL_CONSTR = LOGGI_SLOC_CONSTR
namespace loggi {
    using sloc = std::source_location;
}
#else
#include <cstdint>
#include <string>

//#define LOGGI_SLOC_CONSTR { 0u, 0u, "", ""}
#define LOGGI_SLOC_CONSTR loggi::sloc(__LINE__ , 0u, __FILE__, __PRETTY_FUNCTION__)
#define LOGGI_SLOC_OPT_DFL_CONSTR

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

#endif //LOGGI_SLOC_HXX
#endif
