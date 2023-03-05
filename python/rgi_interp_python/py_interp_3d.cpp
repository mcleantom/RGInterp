//
// Created by tom on 03/03/23.
//
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Interpolator.h"

namespace py = pybind11;

void initInterp3D(py::module_& m)
{
    py::class_<Interpolator3D<double, double, double, Linear, double>>(m, "LinearInterpolator3D")
        .def(py::init<CoordinateAxis<double>, CoordinateAxis<double>, CoordinateAxis<double>, Grid3D<double, Linear>>())
//        .def("interpolate", py::overload_cast<const double, const double, const double>(&Interpolator3D<double, double, double, Linear, double>::interpolate, py::const_))
        .def("interpolate", py::overload_cast<const std::vector<double>&, const std::vector<double>&, const std::vector<double>&>(&Interpolator3D<double, double, double, Linear, double>::interpolate, py::const_));
}