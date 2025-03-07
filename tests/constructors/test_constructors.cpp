#include "sumpy.hpp"
#include <cassert>
#include <iostream>

void test_initializer_list_1D() {
    Sumarray<int> arr = {1, 2, 3, 4};
    // Check values using the 1D indexing (using an initializer list with one index).
    assert(arr[{0}] == 1);
    assert(arr[{1}] == 2);
    assert(arr[{2}] == 3);
    assert(arr[{3}] == 4);
}

void test_initializer_list_2D() {
    Sumarray<int> arr = {{1, 2, 3}, {4, 5, 6}};
    // Check a few values in the 2D array.
    std::initializer_list<int> idx = {0, 0};
    assert(arr[idx] == 1);
    idx = {0, 1};
    assert(arr[idx] == 2);
    idx = {1, 2};
    assert(arr[idx] == 6);
}

int main() {
    test_initializer_list_1D();
    test_initializer_list_2D();
    std::cout << "Constructors tests passed.\n";
    return 0;
}
