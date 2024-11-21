//
// Created by maggu2810 on 8/7/24.
//

#ifndef LOGGI_IMPL_SLOC_HXX
#define LOGGI_IMPL_SLOC_HXX

#include <version>

#define LOGGI_IMPL_SLOC_IMPL_SLOC_ENABLED 1

#if __cpp_lib_source_location >= 201907L

#include <source_location>

#define LOGGI_IMPL_SLOC_DFL_CONSTR_SUPPORT 1
#define LOGGI_IMPL_SLOC_CONSTR ::loggi_impl::sloc{}

#if LOGGI_IMPL_SLOC_IMPL_SLOC_ENABLED
#define LOGGI_IMPL_SLOC_C std::source_location::current()
#else
#define LOGGI_IMPL_SLOC_C {}
#endif

namespace loggi_impl {
    class sloc_ge20 : public std::source_location {
    public:
        sloc_ge20(const std::source_location sloc = LOGGI_IMPL_SLOC_C) // NOLINT(*-explicit-constructor)
            : std::source_location(sloc) {
        }
    };

    using sloc = sloc_ge20;
}

#undef LOGGI_IMPL_SLOC_C

#else

#include <cstdint>
#include <string>

#define LOGGI_IMPL_SLOC_DFL_CONSTR_SUPPORT 0
#if LOGGI_IMPL_SLOC_IMPL_SLOC_ENABLED
#define LOGGI_IMPL_SLOC_CONSTR ::loggi_impl::sloc(__LINE__ , 0u, __FILE__, __PRETTY_FUNCTION__)
#else
#define LOGGI_IMPL_SLOC_CONSTR { 0u, 0u, "", ""}
#endif

namespace loggi_impl {
    class sloc_lt20 {
    public:
        sloc_lt20(int line, std::uint_least32_t column, const char *file_name,
                  const char *function_name) : m_line(line), m_column(column), m_file_name(file_name),
                                               m_function_name(function_name) {
        }

        sloc_lt20(std::uint_least32_t line, std::uint_least32_t column, const char *file_name,
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

    using sloc = sloc_lt20;
}

#endif


#include <cstring>

namespace loggi_impl {
    inline bool sloc_empty(::loggi_impl::sloc sloc) {
        return sloc.line() == 0 && sloc.column() == 0 && strlen(sloc.file_name()) == 0 && strlen(
                   sloc.function_name()) == 0;
    }
}

#endif //LOGGI_IMPL_SLOC_HXX
