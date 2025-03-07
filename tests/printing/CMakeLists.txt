add_executable(test_printing test_printing.cpp)
target_link_libraries(test_printing PRIVATE sumpy)
add_test(NAME test_printing COMMAND test_printing)
