#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <vector>
#include <numeric>
#include <stdexcept>

template <typename T>
class Sumarray
{
public:
    // Constructor for Sumarray
    // shape: address of shape vector
    // data: address of contiguous data vector
    Sumarray(std::vector<int> &shape, std::vector<T> &data)
        : shape(shape), data(data)
    {

        // Validate that shape and data match
        size = 1;
        for (int s : shape)
        {
            size *= s;
        }

        if (size != data.size())
        {
            throw std::invalid_argument("Shape and data size do not match");
        }

        ndim = shape.size();

        strides.resize(ndim);
        strides[ndim - 1] = 1;
        for (int i = ndim - 2; i >= 0; i--)
        {
            strides[i] = strides[i + 1] * shape[i + 1];
        }

        c_style = true;
    }

    // Constructor for 1D Sumarray
    // data: initializer list of (1D) data
    Sumarray(std::initializer_list<T> data)
    {
        ndim = 1;
        shape = {data.size()};
        strides = {1};
        size = data.size();
        c_style = true;
    }

    // Constructor for 2D Sumarray
    // data: initializer list of (2D) data
    Sumarray(std::initializer_list<std::initializer_list<T>> data)
    {

        // Validate that data is an n x m matrix
        int n = data.size();
        int m = data.begin()->size();
        if (n == 0 || m == 0)
        {
            throw std::invalid_argument("Data must be a non-empty matrix");
        }
        for (const auto &row : data)
        {
            if (row.size() != m)
            {
                throw std::invalid_argument(std::format("All rows must have the same length: {} != {}", row.size(), m));
            }
        }

        ndim = 2;
        shape = {n, m};
        strides = {1, n};
        size = n * m;
        c_style = true;
    }

    // Access the element at the given indices
    // This is a reference to the element, so it can be used to modify the element
    T &operator[](std::initializer_list<int> indices)
    {
        if (indices.size() != ndim)
        {
            throw std::invalid_argument(std::format("Number of indices must match the number of dimensions: {} != {}", indices.size(), ndim));
        }

        int index = 0;
        for (int i = 0; i < ndim; i++)
        {
            if (indices[i] < 0 || indices[i] >= shape[i])
            {
                throw std::out_of_range(std::format("Index out of range: {} not in [0, {})", indices[i], shape[i]));
            }
            index += strides[i] * indices[i];
        }
        return data[index];
    }

    // Access a read-only copy element at the given indices
    const T &operator[](std::initializer_list<int> indices) const
    {
        if (indices.size() != ndim)
        {
            throw std::invalid_argument(std::format("Number of indices must match the number of dimensions: {} != {}", indices.size(), ndim));
        }

        int index = 0;
        for (int i = 0; i < ndim; i++)
        {
            if (indices[i] < 0 || indices[i] >= shape[i])
            {
                throw std::out_of_range(std::format("Index out of range: {} not in [0, {})", indices[i], shape[i]));
            }
            index += strides[i] * indices[i];
        }
        return data[index];
    }

    // Print the Sumarray's data
    void print() const
    {
        print_recursive(0, 0, 0);
        std::cout << std::endl;
    }

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
    std::vector<T> arr;
    std::vector<int> shape;
    std::vector<int> strides;

    bool c_style; // True if stored in row-major order.

    int size; // Total number of elements.
    int ndim; // Number of dimensions.

    void print_recursive(int dim, int offset, int indent) const
    {
        // Print elements in the last dimension
        if (dim == ndim - 1)
        {
            // Print the opening bracket
            std::cout << std::string(indent, ' ') << "[";
            for (int i = 0; i < shape[dim]; i++)
            {
                // Print the element since stride is 1
                std::cout << data[offset + i];
                if (i < shape[dim] - 1)
                {
                    std::cout << ", ";
                }
            }
            // Print the closing bracket
            std::cout << "]" << std::endl;
        }
        else
        {
            std::cout << std::string(indent, ' ') << "[";
            // Print each element in the current dimension
            for (int i = 0; i < shape[dim]; i++)
            {
                // Our new offset is the offset of the next element in the current dimension
                // Each iteration increments offset by strides[dim]
                print_recursive(dim + 1, offset + strides[dim] * i, indent + 2);
                if (i < shape[dim] - 1)
                {
                    std::cout << ",\n";
                }
                else
                {
                    std::cout << "\n";
                }
            }
            // Print the closing bracket
            std::cout << std::string(indent, ' ') << "]";
        }
    }
};

#endif