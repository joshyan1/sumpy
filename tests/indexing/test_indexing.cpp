#include "sumpy.hpp"
#include <iostream>
#include <cassert>

void test_valid_indexing() {
    Sumarray<int> arr = {{10, 20, 30}, {40, 50, 60}};
    // Valid indexing tests.
    std::initializer_list<int> idx = {0, 0};
    assert(arr[idx] == 10);
    idx = {0, 1};
    assert(arr[idx] == 20);
    idx = {1, 2};
    assert(arr[idx] == 60);
}

void test_out_of_range() {
    bool caught = false;
    Sumarray<int> arr = {{1, 2, 3}, {4, 5, 6}};
    try {
        // This should throw an exception.
        auto val = arr[{2, 0}];
    } catch (const std::out_of_range&) {
        caught = true;
    }
    assert(caught);
}

int main() {
    test_valid_indexing();
    test_out_of_range();
    std::cout << "Indexing tests passed.\n";
    return 0;
}
