#include "sumpy.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

void test_print_shape() {
    Sumarray<int> arr = {{1, 2, 3}, {4, 5, 6}};
    // Redirect output to a stringstream.
    std::stringstream ss;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());
    
    arr.print_shape();
    
    std::cout.rdbuf(oldCoutStreamBuf);
    std::string output = ss.str();
    
    // Simple check to see if the shape is printed as expected.
    assert(output.find("2, 3") != std::string::npos);
}

void test_print_data() {
    Sumarray<int> arr = {{7, 8}, {9, 10}};
    // Just call print() to ensure it runs without error.
    arr.print();
}

void test_printing() {
    test_print_shape();
    test_print_data();
    std::cout << "Printing tests passed.\n";
}
