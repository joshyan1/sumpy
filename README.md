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