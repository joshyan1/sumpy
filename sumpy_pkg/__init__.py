"""
sumpy - A NumPy-like array library implemented in C++
"""

import os
import sys

# Add the directory containing the compiled module to the Python path
_module_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _module_path not in sys.path:
    sys.path.insert(0, _module_path)

# Also add the build directory to the Python path
_build_path = os.path.join(_module_path, 'build')
if os.path.exists(_build_path) and _build_path not in sys.path:
    sys.path.insert(0, _build_path)

try:
    from sumpy_core import Sumarray_int, Sumarray_float, Sumarray_double
except ImportError:
    raise ImportError(
        "Failed to import the sumpy_core module. Make sure it has been built correctly.\n"
        "Try running: mkdir -p build && cd build && cmake .. && make"
    )

# Define a more user-friendly interface
class array:
    """
    A NumPy-like array class that wraps the C++ Sumarray implementation.
    """
    
    @staticmethod
    def zeros(shape, dtype=float):
        """Create an array of zeros with the given shape."""
        if dtype == int:
            return Sumarray_int.zeros(shape)
        elif dtype == float:
            return Sumarray_float.zeros(shape)
        elif dtype == double:
            return Sumarray_double.zeros(shape)
        else:
            raise TypeError(f"Unsupported dtype: {dtype}")
    
    @staticmethod
    def ones(shape, dtype=float):
        """Create an array of ones with the given shape."""
        if dtype == int:
            return Sumarray_int.ones(shape)
        elif dtype == float:
            return Sumarray_float.ones(shape)
        elif dtype == double:
            return Sumarray_double.ones(shape)
        else:
            raise TypeError(f"Unsupported dtype: {dtype}")
    
    @staticmethod
    def eye(n, dtype=float):
        """Create an identity matrix of size n."""
        if dtype == int:
            return Sumarray_int.eye(n)
        elif dtype == float:
            return Sumarray_float.eye(n)
        elif dtype == double:
            return Sumarray_double.eye(n)
        else:
            raise TypeError(f"Unsupported dtype: {dtype}")
    
    @staticmethod
    def arange(start, stop, step=1, dtype=float):
        """Create an array with evenly spaced values within a given interval."""
        if dtype == int:
            return Sumarray_int.arange(start, stop, step)
        elif dtype == float:
            return Sumarray_float.arange(start, stop, step)
        elif dtype == double:
            return Sumarray_double.arange(start, stop, step)
        else:
            raise TypeError(f"Unsupported dtype: {dtype}")
    
    @staticmethod
    def linspace(start, stop, num=50, endpoint=True, dtype=float):
        """Create an array with evenly spaced values over a specified interval."""
        if dtype == float:
            return Sumarray_float.linspace(start, stop, num, endpoint)[0]
        elif dtype == double:
            return Sumarray_double.linspace(start, stop, num, endpoint)[0]
        elif dtype == int:
            return Sumarray_int.linspace(start, stop, num, endpoint)[0]
        else:
            raise TypeError(f"Unsupported dtype: {dtype}")
    
    @staticmethod
    def full(shape, fill_value, dtype=None):
        """Create an array of given shape and type, filled with fill_value."""
        if dtype is None:
            if isinstance(fill_value, int):
                dtype = int
            elif isinstance(fill_value, float):
                dtype = float
            else:
                dtype = float
        
        if dtype == int:
            return Sumarray_int.full(shape, int(fill_value))
        elif dtype == float:
            return Sumarray_float.full(shape, float(fill_value))
        elif dtype == double:
            return Sumarray_double.full(shape, float(fill_value))
        else:
            raise TypeError(f"Unsupported dtype: {dtype}")

# Define the double type for consistency with NumPy
double = float

# Export the array class and the Sumarray classes
__all__ = ['array', 'Sumarray_int', 'Sumarray_float', 'Sumarray_double', 'double'] 