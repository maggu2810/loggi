cmake_minimum_required(VERSION 3.28)
project(loggi_examples)
add_executable(simple
        src/main.cxx
        #src/test_loggi_backend_sd.cxx
        #src/test_loggi_backend_stderr.cxx
        #src/test_loggi_backend_stdout.cxx
)
#target_compile_definitions(simple PRIVATE LOGGI_BACKEND_DFL=3)
target_link_libraries(simple PRIVATE loggi)