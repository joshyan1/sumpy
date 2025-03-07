#include <iostream>

// Function declarations for each test suite
void test_constructors();
void test_factory();
void test_indexing();
void test_printing();

int main() {
    test_constructors();
    test_factory();
    test_indexing();
    test_printing();
    
    std::cout << "All tests passed!\n";
    return 0;
}