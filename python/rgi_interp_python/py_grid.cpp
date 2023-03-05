//
// Created by tom on 03/03/23.
//
#include "pybind11/pybind11.h"
#include "pybind11/eigen.h"
#include "pybind11/numpy.h"
#include "Grid.h"

namespace py = pybind11;

template <class T>
Eigen::Tensor<T, 3>numpyToEigenTensor3D(
        py::array_t<T, py::array::f_style | py::array::forcecast>& inArray)
{
    py::buffer_info buffer_info = inArray.request();
    T* data = static_cast<T*>(buffer_info.ptr);
    std::vector<ssize_t> shape = buffer_info.shape;
    if (shape.size() != 3) {
        throw std::runtime_error("Array must be three dimensional");
    }
    Eigen::TensorMap<Eigen::Tensor<T, 3>> tensor(data, shape[0], shape[1], shape[2]);
    return Eigen::Tensor<T, 3>(tensor);
}

Grid3D<double, Linear> createGrid(py::array_t<double, py::array::f_style | py::array::forcecast>& inArray, double fillValue, std::string_view name)
{
    return {numpyToEigenTensor3D(inArray), fillValue, name};
}

void initGrid(py::module_& m)
{
    py::class_<Grid3D<double, Linear>>(m, "Grid3D")
        .def(py::init(&createGrid));
}