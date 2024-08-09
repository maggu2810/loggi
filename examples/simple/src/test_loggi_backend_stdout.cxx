//
// Created by maggu2810 on 8/9/24.
//

#undef LOGGI_BACKEND
#define LOGGI_BACKEND 1
#include <loggi/loggi.hxx>
#undef LOGGI_BACKEND

void test_loggi_backend_stdout() {
    loggi::info({}, "{}", "stdout");
}