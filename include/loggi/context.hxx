//
// Created by maggu2810 on 9/18/24.
//

#ifndef LOGGI_CONTEXT_HXX
#define LOGGI_CONTEXT_HXX

#include <loggi/impl/sloc.hxx>
#include <loggi/impl/constexpr.hxx>

#include <algorithm>
#include <sstream>
#include <thread>

#define LOGGI_SUPPORTED_CONTEXT_DFL_CONSTR LOGGI_IMPL_SLOC_DFL_CONSTR_SUPPORT
#define LOGGI_CONTEXT_CONSTR ::loggi::context(LOGGI_IMPL_SLOC_CONSTR)

namespace loggi {
    class context {
        static LOGGI_IMPL_CONSTEXPR_GE23 std::string tid_to_string(const std::thread::id &tid) {
            std::stringstream ss;
            ss << tid;
            return ss.str();
        }

    public:
        context // NOLINT(*-explicit-constructor)
        (const ::loggi_impl::sloc &sloc
#if LOGGI_IMPL_SLOC_DFL_CONSTR_SUPPORT
                 = LOGGI_IMPL_SLOC_CONSTR
#endif
         ,
         const std::thread::id &tid = std::this_thread::get_id()) : m_sloc(sloc), m_tid(tid_to_string(tid)) {
        }

        const ::loggi_impl::sloc &sloc() const {
            return m_sloc;
        }

        const std::string &tid() const {
            return m_tid;
        }

    private:
        ::loggi_impl::sloc m_sloc;
        std::string m_tid;
    };
}

#endif //LOGGI_CONTEXT_HXX
