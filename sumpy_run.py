#!/usr/bin/env python3

import sumpy_pkg as sp

def main():
    print("Creating a zeros array:")
    zeros = sp.array.zeros([2, 3], dtype=int)
    zeros.print()
    zeros.print_shape()
    print()

    print("Creating a ones array:")
    ones = sp.array.ones([3, 2], dtype=float)
    ones.print()
    ones.print_shape()
    print()

    print("Creating an identity matrix:")
    eye = sp.array.eye(3, dtype=int)
    eye.print()
    eye.print_shape()
    print()

    print("Creating an array with arange:")
    arange = sp.array.arange(0, 10, 2, dtype=int)
    arange.print()
    arange.print_shape()
    print()

    print("Creating an array with linspace:")
    linspace = sp.array.linspace(0, 1, 5, dtype=float)
    linspace.print()
    linspace.print_shape()
    print()

    print("Creating a full array:")
    full = sp.array.full([2, 2], 42, dtype=int)
    full.print()
    full.print_shape()
    print()

if __name__ == "__main__":
    # This will only run when the script is executed directly
    # When imported, this block is not executed
    main() 