# sumpy

here's my small, less efficient, and likely incorrect implementation of numpy in C++, built without external dependencies, and from scratch.

hopefully, I learn some C++ through this.

## build and run

```bash
brew install fmt

# Install pybind11 (macOS)
brew install pybind11

# Or using pip
pip install pybind11
```

```bash
mkdir -p build
cd build
cmake ..
make
cd ..
```

## functionalities

### 1. array creation and initialization
- [x] basic array construction (1d and 2d)
- [x] zeros(shape)
- [x] ones(shape)
- [x] eye(n)
- [x] arange(start, stop, step)
- [x] linspace(start, stop, num)
- [x] full(shape, value)

### 2. indexing and slicing
- [x] integer indexing
- [x] bounds checking
- [ ] row/column slicing (e.g., arr(0) for first row)
- [ ] range slicing (start:stop:step)
- [ ] view-based slicing (no data copying)

### 3. basic arithmetic (elementwise)
- [ ] addition (+)
- [ ] subtraction (-)
- [ ] multiplication (*)
- [ ] division (/)
- [ ] scalar operations
- [ ] unary operations (-arr, abs(arr))

### 4. reductions and aggregations
- [ ] sum()
- [ ] min(), max()
- [ ] mean()
- [ ] std()
- [ ] axis-based reductions (e.g., sum(axis=0))

### 5. broadcasting
- [ ] shape compatibility checking
- [ ] broadcasted arithmetic operations
- [ ] efficient memory handling for broadcasts

### 6. shape manipulation
- [ ] reshape()
- [ ] transpose()
- [ ] flatten()
- [ ] ravel()

### 7. memory management
- [ ] shared pointer implementation
- [ ] view-based operations
- [ ] copy-on-write optimization

### 8. more stuff
- [ ] boolean masking
- [ ] fancy indexing
- [ ] matrix multiplication (matmul/dot)
- [ ] simd optimizations
- [ ] parallel operations
