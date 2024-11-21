#define LOGGI_BACKEND 0
#define LOGGI_FRONTEND 0

#include <loggi/loggi.hxx>
#include <iostream>
#include <cstdlib>

#ifndef LOGGI_BACKEND
void loggi::backend::log(const ::loggi::context &ctx, ::loggi::level lvl, const std::string &str) {
    std::cout << str << std::endl;
}
#endif

#if LOGGI_FRONTEND == 0
#elif LOGGI_FRONTEND == 1
void pf() {
    LOGGI_INFO("%s", "hello");
    LOGGI_WARN("%d %d %d", 1, 2, 3);
    loggi::warn(LOGGI_IMPL_SLOC_CONSTR, "%d %d %d", 1, 2, 3);
}
#endif

int main(int argc, char *argv[]) {
    setenv("LOGGI_TARGET", "stderr", 1);

#if LOGGI_FRONTEND == 0
    LOGGI_INFO("{}", "hello");
    LOGGI_WARN("{} {} {}", 1, 2, 3);
    loggi::warn(LOGGI_CONTEXT_CONSTR, "{} {} {}", 1, 2, 3);

#if LOGGI_SUPPORTED_CONTEXT_DFL_CONSTR
    loggi::warn({}, "using ctx dfl constr, {} {} {}", 1, 2, 3);
    //loggi::warn({}, "{} {} {}", 1, 2);
#endif

#elif LOGGI_FRONTEND == 1
    for (int i = 0; i < 3000; ++i) {
        pf();
    }
#endif

    return 0;
}
