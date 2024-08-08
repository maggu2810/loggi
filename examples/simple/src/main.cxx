#include <loggi/loggi.hxx>
#include <iostream>

int main(int argc, char *argv[]) {
    LOGGI_INFO("{}", "hello");
    LOGGI_WARN("{} {} {}", 1, 2, 3);
    loggi::warn(LOGGI_SLOC_CONSTR, "{} {} {}", 1, 2, 3);
    //loggi::warn({}, "{} {} {}", 1, 2, 3);
    //loggi::warn({}, "{} {} {}", 1, 2);
    return 0;
}
