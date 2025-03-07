// main.cpp
#include <iostream>
#include "sumpy.hpp"

int main()
{
    std::cout << "Creating a 1D Sumarray:" << std::endl;
    Sumarray<int> arr1 = {1, 2, 3, 4, 5};
    arr1.print(); // Print the contents in a nice format.
    std::cout << "Shape: ";
    arr1.print_shape(); // Print the shape.
    std::cout << "Element at index {2}: " << arr1[{2}] << std::endl;
    std::cout << std::endl;

    std::cout << "Creating a 2D Sumarray:" << std::endl;
    Sumarray<int> arr2 = {{1, 2, 3}, {4, 5, 6}};
    arr2.print();
    std::cout << "Shape: ";
    arr2.print_shape();
    // Access element at row 1, column 2 (0-based indexing)
    std::cout << "Element at indices {1, 2}: " << arr2[{1, 2}] << std::endl;
    std::cout << std::endl;

    std::vector<int> shape = {2, 3};
    std::vector<int> data = {10, 20, 30, 40, 50, 60};
    Sumarray<int> arr3(shape, data);
    std::cout << "Creating a 2D Sumarray using explicit shape and data:" << std::endl;
    arr3.print();
    std::cout << "Shape: ";
    arr3.print_shape();
    std::cout << "Element at indices {0, 2}: " << arr3[{0, 2}] << std::endl;
    std::cout << "Element at indices {1, 0}: " << arr3[{1, 0}] << std::endl;

    return 0;
}
