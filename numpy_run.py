#!/usr/bin/env python3

import numpy as np

def main():
    print("Creating a zeros array:")
    zeros = np.zeros((2, 3), dtype=int)
    print(zeros)
    print(f"Shape: {zeros.shape}")
    print()

    print("Creating a ones array:")
    ones = np.ones((3, 2), dtype=float)
    print(ones)
    print(f"Shape: {ones.shape}")
    print()

    print("Creating an identity matrix:")
    eye = np.eye(3, dtype=int)
    print(eye)
    print(f"Shape: {eye.shape}")
    print()

    print("Creating an array with arange:")
    arange = np.arange(0, 10, 2, dtype=int)
    print(arange)
    print(f"Shape: {arange.shape}")
    print()

    print("Creating an array with linspace:")
    linspace = np.linspace(0, 1, 5, dtype=float)
    print(linspace)
    print(f"Shape: {linspace.shape}")
    print()

    print("Creating a full array:")
    full = np.full((2, 2), 42, dtype=int)
    print(full)
    print(f"Shape: {full.shape}")
    print()

if __name__ == "__main__":
    main() 