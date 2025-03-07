#!/usr/bin/env python3
"""
Tests for the Python bindings of the sumpy library.
"""

import sys
import os
import unittest

# Add the parent directory to the Python path
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

# Import the sumpy package
try:
    from sumpy_pkg import array
except ImportError:
    print("Failed to import sumpy_pkg. Make sure the package is built and installed.")
    sys.exit(1)

class TestSumpyBindings(unittest.TestCase):
    """Test cases for the sumpy Python bindings."""

    def test_zeros(self):
        """Test the zeros function."""
        zeros = array.zeros([2, 3], dtype=int)
        # We can't directly check the values, but we can check that it doesn't crash
        zeros.print()
        zeros.print_shape()

    def test_ones(self):
        """Test the ones function."""
        ones = array.ones([3, 2], dtype=float)
        ones.print()
        ones.print_shape()

    def test_eye(self):
        """Test the eye function."""
        eye = array.eye(3, dtype=int)
        eye.print()
        eye.print_shape()

    def test_arange(self):
        """Test the arange function."""
        arange = array.arange(0, 10, 2, dtype=int)
        arange.print()
        arange.print_shape()

    def test_linspace(self):
        """Test the linspace function."""
        linspace = array.linspace(0, 1, 5, dtype=float)
        linspace.print()
        linspace.print_shape()

    def test_full(self):
        """Test the full function."""
        full = array.full([2, 2], 42, dtype=int)
        full.print()
        full.print_shape()

if __name__ == "__main__":
    unittest.main() 