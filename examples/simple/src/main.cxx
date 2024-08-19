#define LOGGI_FRONTEND 1

#include <loggi/loggi.hxx>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) {
    setenv("LOGGI_TARGET", "journal", 1);

#if LOGGI_FRONTEND == 0
    LOGGI_INFO("{}", "hello");
    LOGGI_WARN("{} {} {}", 1, 2, 3);
    loggi::warn(LOGGI_SLOC_CONSTR, "{} {} {}", 1, 2, 3);
    //loggi::warn({}, "{} {} {}", 1, 2, 3);
    //loggi::warn({}, "{} {} {}", 1, 2);
#else
    LOGGI_INFO("%s", "hello");
    LOGGI_WARN("%d %d %d", 1, 2, 3);
    loggi::warn(LOGGI_SLOC_CONSTR, "%d %d %d", 1, 2, 3);
#endif

    return 0;
}
