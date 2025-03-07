# sumpy

Here's my small, less efficient, and likely incorrect implementation of numpy in C++, built without external dependencies, and from scratch.

Hopefully, I learn some C++ through this.

## build and run

```shell
# Build the project
cmake -B build
cmake --build build

# Run the main program
./build/main
```

## tests

Run tests in either way

1. Run tests directly (with detailed output):
```shell
./build/tests/sumpy_tests
```

2. Run tests using CTest (summary output):
```shell
cd build
ctest
```

## functionalities

- [x] 1D and 2D array construction and initialization
- [x] Factory functions (zeros, ones, eye, arange, linspace)
- [x] Array indexing
- [x] Array printing and shape display
- [ ] Array operations (addition, subtraction, multiplication, division)
- [ ] Array functions (sum, mean, max, min, etc.)
- [ ] Broadcasting
- [ ] Dot product
- [ ] Matrix multiplication
- [ ] Transpose
- [ ] Reshape
- [ ] Flatten
