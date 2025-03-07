#include "sumpy.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

// Test for full, zeros, ones
void test_full_zeros_ones() {
    std::vector<int> shape = {2, 3};
    Sumarray<int> full_arr = Sumarray<int>::full(shape, 5);
    Sumarray<int> zeros_arr = Sumarray<int>::zeros(shape);
    Sumarray<int> ones_arr = Sumarray<int>::ones(shape);

    // Test full
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j) {
            std::initializer_list<int> idx = {i, j};
            assert(full_arr[idx] == 5);
        }

    // Test zeros
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j) {
            std::initializer_list<int> idx = {i, j};
            assert(zeros_arr[idx] == 0);
        }

    // Test ones
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j) {
            std::initializer_list<int> idx = {i, j};
            assert(ones_arr[idx] == 1);
        }
}

// Test for eye
void test_eye() {
    int n = 4;
    Sumarray<int> identity = Sumarray<int>::eye(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            std::initializer_list<int> idx = {i, j};
            assert(identity[idx] == (i == j ? 1 : 0));
        }
}

// Test for arange
void test_arange() {
    // Example: arange from 0 to 10 with step 2 => 0, 2, 4, 6, 8.

    Sumarray<int> arr = Sumarray<int>::arange(0, 10, 2);
    std::initializer_list<int> idx = {0};
    assert(arr[idx] == 0);
    idx = {1};
    assert(arr[idx] == 2);
    idx = {2};
    assert(arr[idx] == 4);
    idx = {3};
    assert(arr[idx] == 6);
    idx = {4};
    assert(arr[idx] == 8);
}

// Test for linspace.
void test_linspace() {
    // Example: linspace from 0.0 to 1.0 with 5 elements.
    auto [arr, step] = Sumarray<double>::linspace(0.0, 1.0, 5);
    double tol = 1e-9;
    assert(std::fabs(arr[{0}] - 0.0) < tol);
    assert(std::fabs(arr[{1}] - 0.25) < tol);
    assert(std::fabs(arr[{2}] - 0.5) < tol);
    assert(std::fabs(arr[{3}] - 0.75) < tol);
    assert(std::fabs(arr[{4}] - 1.0) < tol);
}

void test_factory() {
    test_full_zeros_ones();
    test_eye();
    test_arange();
    test_linspace();
    std::cout << "Factory functions tests passed.\n";
}
