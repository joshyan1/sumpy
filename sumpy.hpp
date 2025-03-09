#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <vector>
#include <numeric>
#include <stdexcept>
#include <fmt/core.h>
#include <iostream>
#include <string>
#include <utility>
#include <cmath> // Added for std::ceil

template <typename T>
class Sumarray
{
public:
    /*
    Constructors
    */

    // Constructor for Sumarray from explicit shape and data vectors.
    Sumarray(const std::vector<int> &shape, const std::vector<T> &data)
        : shape(shape), data(std::make_shared<std::vector<T>>(data))
    {
        offset = 0;

        // Validate that shape and data match.
        size = 1;
        for (int s : shape)
        {
            size *= s;
        }
        if (size != static_cast<int>(data.size()))
        {
            throw std::invalid_argument("Shape and data size do not match");
        }
        ndim = shape.size();

        // Compute strides for C-style row-major order.
        strides.resize(ndim);
        if (ndim > 0)
        {
            strides[ndim - 1] = 1;
            for (int i = ndim - 2; i >= 0; i--)
            {
                strides[i] = strides[i + 1] * shape[i + 1];
            }
        }
        c_style = true;
    }

    // Constructor for 1D Sumarray using an initializer list.
    Sumarray(std::initializer_list<T> init)
    {
        offset = 0;
        ndim = 1;
        shape = {static_cast<int>(init.size())};
        strides = {1};
        size = static_cast<int>(init.size());
        c_style = true;
        data = std::make_shared<std::vector<T>>(init);
    }

    // Constructor for 2D Sumarray using a nested initializer list.
    Sumarray(std::initializer_list<std::initializer_list<T>> init)
    {
        // Validate that data is a non-empty matrix with all rows of equal length.
        int n = static_cast<int>(init.size());
        int m = static_cast<int>(init.begin()->size());
        if (n == 0 || m == 0)
        {
            throw std::invalid_argument("Data must be a non-empty matrix");
        }
        for (const auto &row : init)
        {
            if (static_cast<int>(row.size()) != m)
            {
                throw std::invalid_argument(fmt::format("All rows must have the same length: {} != {}", row.size(), m));
            }
        }

        offset = 0;
        ndim = 2;
        shape = {n, m};
        strides = {m, 1}; // For row-major order, row stride equals number of columns.
        size = n * m;
        c_style = true;
        // Initialize the data pointer before inserting elements.
        data = std::make_shared<std::vector<T>>();
        data->reserve(size);
        // Flatten the 2D initializer list into the member vector 'data'.
        for (const auto &row : init)
        {
            data->insert(data->end(), row.begin(), row.end());
        }
    }

    /*
    Static utility functions for creating Sumarrays.
    */

    static Sumarray<T> full(const std::vector<int> &shape, T value)
    {
        int size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<int>());
        std::vector<T> data(size, value);
        return Sumarray<T>(shape, data);
    }

    static Sumarray<T> zeros(const std::vector<int> &shape)
    {
        return full(shape, static_cast<T>(0));
    }

    static Sumarray<T> ones(const std::vector<int> &shape)
    {
        return full(shape, static_cast<T>(1));
    }

    // Creates an identity matrix of size n.
    static Sumarray<T> eye(int n)
    {
        std::vector<int> shape = {n, n};
        std::vector<T> data(n * n, static_cast<T>(0));
        for (int i = 0; i < n; i++)
        {
            data[i * (n + 1)] = static_cast<T>(1);
        }
        return Sumarray<T>(shape, data);
    }

    // Numpy's arange function.
    static Sumarray<T> arange(T start, T stop, T step = 1)
    {
        // Ensure size is an integer
        int size = static_cast<int>(std::ceil((stop - start) / step));
        std::vector<int> shape = {size};
        std::vector<T> data(size);

        for (int i = 0; i < size; i++)
        {
            data[i] = start + i * step;
        }
        return Sumarray<T>(shape, data);
    }

    // Numpy's linspace function
    static std::pair<Sumarray<T>, T> linspace(T start, T stop, int num, bool endpoint = true)
    {
        if (num < 1)
        {
            throw std::invalid_argument("num must be greater than 0");
        }

        std::vector<T> data(num);
        std::vector<int> shape = {num};

        T step = (num == 1) ? 0 : (stop - start) / (endpoint ? (num - 1) : num);

        for (int i = 0; i < num; i++)
        {
            data[i] = start + i * step;
        }

        return {Sumarray<T>(shape, data), step};
    }

    /*
    Indexing and slicing
    */

    // Element access (non-const) using an initializer list for indices.
    T &operator[](std::initializer_list<int> indices)
    {
        if (indices.size() != static_cast<size_t>(ndim))
        {
            throw std::invalid_argument(fmt::format("Number of indices must match the number of dimensions: {} != {}", indices.size(), ndim));
        }
        int index = offset;
        auto it = indices.begin();
        for (int i = 0; i < ndim; i++)
        {
            if (*it < 0 || *it >= shape[i])
            {
                throw std::out_of_range(fmt::format("Index out of range: {} not in [0, {})", *it, shape[i]));
            }
            index += strides[i] * *it;
            ++it;
        }
        return (*data)[index];
    }

    // Element access (const) using an initializer list for indices.
    const T &operator[](std::initializer_list<int> indices) const
    {
        if (indices.size() != static_cast<size_t>(ndim))
        {
            throw std::invalid_argument(fmt::format("Number of indices must match the number of dimensions: {} != {}", indices.size(), ndim));
        }
        int index = offset;
        auto it = indices.begin();
        for (int i = 0; i < ndim; i++)
        {
            if (*it < 0 || *it >= shape[i])
            {
                throw std::out_of_range(fmt::format("Index out of range: {} not in [0, {})", *it, shape[i]));
            }
            index += strides[i] * *it;
            ++it;
        }
        return (*data)[index];
    }

    // Advanced indexing
    Sumarray operator()(const std::vector<int> &indices)
    {
        if (ndim <= 1)
        {
            throw std::invalid_argument("Cannot slice a 1D array");
        }

        for (int index : indices)
        {
            if (index < 0 || index >= shape[0])
            {
                throw std::out_of_range(fmt::format("Index out of range: {} not in [0, {})", index, shape[0]));
            }
        }

        // Calculates the size of one element in the first dimension.
        int blockSize = 1;
        for (size_t i = 1; i < shape.size(); i++)
        {
            blockSize *= shape[i];
        }

        std::vector<int> newShape(shape.size());
        std::vector<int> newStrides(strides.size());

        newShape[0] = indices.size();
        newStrides[0] = strides[0];

        // Copy shape and strides for remaining dimensions.
        for (size_t i = 1; i < shape.size(); i++)
        {
            newShape[i] = shape[i];
            newStrides[i] = strides[i];
        }

        std::vector<T> newData(indices.size() * blockSize);

        // Copy the data from the original Sumarray to the new Sumarray.
        for (size_t i = 0; i < indices.size(); i++)
        {
            std::copy(data->begin() + (offset + indices[i] * strides[0]),
                      data->begin() + (offset + (indices[i] + 1) * strides[0]),
                      newData.begin() + i * blockSize);
        }

        return Sumarray(newShape, newData);
    }

    // Row slicing
    Sumarray operator()(int index)
    {
        if (index < 0 || index >= shape[0])
        {
            throw std::out_of_range(fmt::format("Index out of range: {} not in [0, {})", index, shape[0]));
        }

        // New shape: remove the first dimension.
        std::vector<int> newShape(shape.begin() + 1, shape.end());
        std::vector<int> newStrides(strides.begin() + 1, strides.end());

        // Compute new offset.
        int newOffset = offset + index * strides[0];

        // Return a view that drops the first dimension.
        return Sumarray(newShape, data, newOffset, newStrides);
    }

    /*
        Print methods
        */

    // Print the Sumarray's data in a nested format.
    void print() const
    {
        print_recursive(0, offset, 0);
        std::cout << std::endl;
    }

    // Print the shape of the Sumarray.
    void print_shape() const
    {
        std::cout << "[";
        for (int i = 0; i < ndim; i++)
        {
            std::cout << shape[i];
            if (i < ndim - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

private:
    /*
    Member variables
    */

    std::shared_ptr<std::vector<T>> data; // Pointer to the data vector.
    std::vector<int> shape;
    std::vector<int> strides;
    bool c_style; // True if stored in row-major order.
    int offset;   // Offset of the first element in the data vector.
    int size;     // Total number of elements.
    int ndim;     // Number of dimensions.

    // View constructor that creates a view sharing the same data.
    Sumarray(const std::vector<int> &shape, std::shared_ptr<std::vector<T>> data, int offset, const std::vector<int> &strides)
        : shape(shape), data(data), offset(offset), strides(strides), c_style(true)
    {
        ndim = shape.size();
        size = 1;
        for (int s : shape)
        {
            size *= s;
        }
    }

    /*
    Private helper functions
    */

    // Helper function: recursively print the array in a nested format.
    void print_recursive(int dim, int offset, int indent) const
    {
        if (dim == ndim - 1)
        {
            std::cout << std::string(indent, ' ') << "[";
            for (int i = 0; i < shape[dim]; i++)
            {
                std::cout << (*data)[offset + i];
                if (i < shape[dim] - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << "]";
        }
        else
        {
            std::cout << std::string(indent, ' ') << "[\n";
            for (int i = 0; i < shape[dim]; i++)
            {
                print_recursive(dim + 1, offset + strides[dim] * i, indent + 2);
                if (i < shape[dim] - 1)
                    std::cout << ",\n";
                else
                    std::cout << "\n";
            }
            std::cout << std::string(indent, ' ') << "]";
        }
    }
};

#endif
