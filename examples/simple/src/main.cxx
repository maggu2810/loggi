#if 0
#include <loggi/loggi.hxx>
#endif
#include <iostream>
#include <cstdlib>

void test_loggi_backend_sd();

void test_loggi_backend_stderr();

void test_loggi_backend_stdout();

int main(int argc, char *argv[]) {
#if 0
    setenv("LOGGI_TARGET", "journal", 1);
    LOGGI_INFO("{}", "hello");
    LOGGI_WARN("{} {} {}", 1, 2, 3);
    loggi::warn(LOGGI_SLOC_CONSTR, "{} {} {}", 1, 2, 3);
    //loggi::warn({}, "{} {} {}", 1, 2, 3);
    //loggi::warn({}, "{} {} {}", 1, 2);
#endif

    test_loggi_backend_sd();
    test_loggi_backend_stderr();
    test_loggi_backend_stdout();


    return 0;
}
