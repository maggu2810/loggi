#include <loggi/loggi.hxx>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) {
    setenv("LOGGI_TARGET", "stderr", 1);
    LOGGI_INFO("{}", "hello");
    LOGGI_WARN("{} {} {}", 1, 2, 3);
    loggi::warn(LOGGI_SLOC_CONSTR, "{} {} {}", 1, 2, 3);
    //loggi::warn({}, "{} {} {}", 1, 2, 3);
    //loggi::warn({}, "{} {} {}", 1, 2);

    return 0;
}
