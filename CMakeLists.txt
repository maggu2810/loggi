cmake_minimum_required(VERSION 3.28)

set(BUILD_SHARED_LIBS ON)
LIST(PREPEND CMAKE_PREFIX_PATH "/home/maggu2810/workspace/projects/oss/fmt_8.1.1.install")

project(loggi LANGUAGES CXX VERSION 0.0.1)

add_library(loggi
        include/loggi/level.hxx
        include/loggi/loggi.hxx
        include/loggi/loggi_compat_fmt.hxx
        include/loggi/loggi_compat_sloc.hxx
        include/loggi/loggi_compat_unreachable.hxx
        include/loggi/loggi_impl.hxx
        src/loggi_impl.cxx
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
target_link_libraries(loggi PRIVATE systemd)
if (COMPILE_FEATURE STREQUAL cxx_std_23)
    target_compile_definitions(loggi PUBLIC SLOG_IMPL_STD_FORMAT=1 SLOG_IMPL_STD_SLOC=1 SLOC_IMPL_STD_UNREACHABLE=1)
elseif (COMPILE_FEATURE STREQUAL cxx_std_20)
    target_compile_definitions(loggi PUBLIC SLOG_IMPL_STD_FORMAT=1 SLOG_IMPL_STD_SLOC=1 SLOC_IMPL_STD_UNREACHABLE=0)
elseif (COMPILE_FEATURE STREQUAL cxx_std_17)
    target_compile_definitions(loggi PUBLIC SLOG_IMPL_STD_FORMAT=0 SLOG_IMPL_STD_SLOC=0 SLOC_IMPL_STD_UNREACHABLE=0)
    find_package(fmt REQUIRED)
    target_link_libraries(loggi PUBLIC fmt::fmt)
endif ()


add_subdirectory(examples/simple)