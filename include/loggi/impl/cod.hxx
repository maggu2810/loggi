//
// Created by maggu2810 on 9/19/24.
//

#ifndef LOGGI_IMPL_COD_HXX
#define LOGGI_IMPL_COD_HXX

#include <cstdlib>

namespace loggi_impl {
  class cod_free {
  public:
    constexpr explicit cod_free(void *ptr) : m_ptr(ptr) {
    }

    LOGGI_IMPL_CONSTEXPR_GE20 ~cod_free() {
      free(m_ptr);
    }

  private:
    void *m_ptr;
  };
}

#endif //LOGGI_IMPL_COD_HXX
