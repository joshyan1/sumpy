# Enable testing
enable_testing()

# Create a single test executable
add_executable(sumpy_tests 
    tests.cpp
    test_constructors.cpp
    test_factory.cpp
    test_indexing.cpp
    test_printing.cpp
)

# Link against sumpy and any testing framework if used
target_link_libraries(sumpy_tests PRIVATE sumpy)

# Register the test
add_test(NAME sumpy_tests COMMAND sumpy_tests)