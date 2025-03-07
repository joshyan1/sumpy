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

## Functionalities

### 1. Array Creation and Initialization
- [x] Basic array construction (1D and 2D)
- [x] zeros(shape)
- [x] ones(shape)
- [x] eye(n)
- [x] arange(start, stop, step)
- [x] linspace(start, stop, num)
- [ ] full(shape, value)

### 2. Indexing and Slicing
- [x] Integer indexing
- [x] Bounds checking
- [ ] Row/column slicing (e.g., arr(0) for first row)
- [ ] Range slicing (start:stop:step)
- [ ] View-based slicing (no data copying)

### 3. Basic Arithmetic (Elementwise)
- [ ] Addition (+)
- [ ] Subtraction (-)
- [ ] Multiplication (*)
- [ ] Division (/)
- [ ] Scalar operations
- [ ] Unary operations (-arr, abs(arr))

### 4. Reductions and Aggregations
- [ ] sum()
- [ ] min(), max()
- [ ] mean()
- [ ] std()
- [ ] Axis-based reductions (e.g., sum(axis=0))

### 5. Broadcasting
- [ ] Shape compatibility checking
- [ ] Broadcasted arithmetic operations
- [ ] Efficient memory handling for broadcasts

### 6. Shape Manipulation
- [ ] reshape()
- [ ] transpose()
- [ ] flatten()
- [ ] ravel()

### 7. Memory Management
- [ ] Shared pointer implementation
- [ ] View-based operations
- [ ] Copy-on-write optimization

### 8. More Stuff
- [ ] Boolean masking
- [ ] Fancy indexing
- [ ] Matrix multiplication (matmul/dot)
- [ ] SIMD optimizations
- [ ] Parallel operations
