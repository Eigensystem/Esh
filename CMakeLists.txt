cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)
project(Esh LANGUAGES CXX)

aux_source_directory(src LIB_SOURCES)
add_library(EshLib STATIC ${LIB_SOURCES})

add_executable(test esh.cc)
target_include_directories(test PUBLIC src)
target_link_libraries(test EshLib)