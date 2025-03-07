#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "sumpy.hpp"

namespace py = pybind11;

template <typename T>
void declare_sumarray(py::module &m, const std::string &typestr) {
    using Class = Sumarray<T>;
    std::string pyclass_name = std::string("Sumarray_") + typestr;
    
    py::class_<Class>(m, pyclass_name.c_str())
        .def(py::init<const std::vector<int>&, const std::vector<T>&>())
        .def("__getitem__", [](const Class &arr, py::list indices) {
            std::vector<int> idx_vec;
            for (auto item : indices) {
                idx_vec.push_back(py::cast<int>(item));
            }
            
            // Convert vector to initializer_list using a workaround
            // We need to use a lambda to capture the vector and pass its elements as an initializer_list
            auto get_element = [&arr, &idx_vec]() -> T {
                switch (idx_vec.size()) {
                    case 1:
                        return arr[{idx_vec[0]}];
                    case 2:
                        return arr[{idx_vec[0], idx_vec[1]}];
                    case 3:
                        return arr[{idx_vec[0], idx_vec[1], idx_vec[2]}];
                    case 4:
                        return arr[{idx_vec[0], idx_vec[1], idx_vec[2], idx_vec[3]}];
                    default:
                        throw std::runtime_error("Unsupported number of dimensions");
                }
            };
            
            return get_element();
        })
        .def("__setitem__", [](Class &arr, py::list indices, T value) {
            std::vector<int> idx_vec;
            for (auto item : indices) {
                idx_vec.push_back(py::cast<int>(item));
            }
            
            // Convert vector to initializer_list using a workaround
            auto set_element = [&arr, &idx_vec, &value]() {
                switch (idx_vec.size()) {
                    case 1:
                        arr[{idx_vec[0]}] = value;
                        break;
                    case 2:
                        arr[{idx_vec[0], idx_vec[1]}] = value;
                        break;
                    case 3:
                        arr[{idx_vec[0], idx_vec[1], idx_vec[2]}] = value;
                        break;
                    case 4:
                        arr[{idx_vec[0], idx_vec[1], idx_vec[2], idx_vec[3]}] = value;
                        break;
                    default:
                        throw std::runtime_error("Unsupported number of dimensions");
                }
            };
            
            set_element();
        })
        .def("print", &Class::print)
        .def("print_shape", &Class::print_shape)
        .def_static("zeros", &Class::zeros)
        .def_static("ones", &Class::ones)
        .def_static("eye", &Class::eye)
        .def_static("arange", &Class::arange)
        .def_static("linspace", &Class::linspace)
        .def_static("full", &Class::full);
}

PYBIND11_MODULE(sumpy_core, m) {
    m.doc() = "Python bindings for Sumarray C++ library";
    
    declare_sumarray<int>(m, "int");
    declare_sumarray<float>(m, "float");
    declare_sumarray<double>(m, "double");
} 