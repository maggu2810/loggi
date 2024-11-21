cmake_minimum_required(VERSION 3.28)

set(BUILD_SHARED_LIBS ON)
LIST(PREPEND CMAKE_PREFIX_PATH "/home/maggu2810/workspace/projects/oss/fmt_8.1.1.install")

project(loggi LANGUAGES CXX VERSION 0.0.1)

add_library(loggi
        include/loggi/level.hxx
        include/loggi/loggi.hxx

        include/loggi/context.hxx
        include/loggi/impl/cod.hxx
        include/loggi/impl/fmt.hxx
        include/loggi/impl/sloc.hxx
        include/loggi/impl/unreachable.hxx

        include/loggi/backend/backend.hxx

        include/loggi/backend/backend_hdrgen.hxx

        include/loggi/backend/backend_sd.hxx
        src/backend_sd.cxx

        include/loggi/backend/backend_stderr.hxx
        include/loggi/backend/backend_stdout.hxx
        src/backend_ostream.hxx
        src/backend_stderr.cxx
        src/backend_stdout.cxx

        include/loggi/backend/backend_dynamic.hxx
        src/backend_dynamic.cxx

        include/loggi/impl/format.hxx
        include/loggi/loggi_format.hxx

        include/loggi/impl/printf.hxx
        include/loggi/loggi_printf.hxx
)

set_target_properties(loggi PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
target_include_directories(loggi PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        src
)

set(COMPILE_FEATURE cxx_std_23)
target_compile_features(loggi PUBLIC ${COMPILE_FEATURE})
target_link_libraries(loggi PUBLIC systemd)
if (COMPILE_FEATURE STREQUAL cxx_std_23)
    target_compile_definitions(loggi PUBLIC LOGGI_IMPL_STD_FORMAT=1)
elseif (COMPILE_FEATURE STREQUAL cxx_std_20)
    target_compile_definitions(loggi PUBLIC LOGGI_IMPL_STD_FORMAT=1)
elseif (COMPILE_FEATURE STREQUAL cxx_std_17)
    target_compile_definitions(loggi PUBLIC LOGGI_IMPL_STD_FORMAT=0)
    find_package(fmt REQUIRED)
    target_link_libraries(loggi PUBLIC fmt::fmt)
endif ()


add_subdirectory(examples/simple)