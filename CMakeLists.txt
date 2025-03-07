cmake_minimum_required(VERSION 3.15)
project(sumpy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(fmt REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

# Create the C++ interface library
add_library(sumpy INTERFACE)
target_include_directories(sumpy INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sumpy INTERFACE fmt::fmt)

# Create the main executable
add_executable(main main.cpp)
target_link_libraries(main PRIVATE sumpy)

# Create the Python module
pybind11_add_module(sumpy_core sumpy_module.cpp)
target_link_libraries(sumpy_core PRIVATE sumpy)

# Enable testing and add your tests.
enable_testing()
add_subdirectory(tests)
