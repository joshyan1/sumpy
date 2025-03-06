cmake_minimum_required(VERSION 3.15)
project(sumpy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)

add_library(sumpy INTERFACE)
target_include_directories(sumpy INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sumpy INTERFACE fmt::fmt)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE sumpy) 