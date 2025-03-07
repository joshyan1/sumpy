add_executable(test_indexing test_indexing.cpp)
target_link_libraries(test_indexing PRIVATE sumpy)
add_test(NAME test_indexing COMMAND test_indexing)
