cmake_minimum_required(VERSION 3.28)
project(loggi_examples)
add_executable(simple src/main.cxx)
target_link_libraries(simple PRIVATE loggi)