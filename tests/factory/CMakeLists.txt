add_executable(test_factory test_factory.cpp)
target_link_libraries(test_factory PRIVATE sumpy)
add_test(NAME test_factory COMMAND test_factory)
