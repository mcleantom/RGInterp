//
// Created by tom on 03/03/23.
//
#include <pybind11/pybind11.h>
#include "Axis.h"

namespace py = pybind11;

void initAxis(py::module_& m) {
    py::class_<CoordinateAxis<double>>(m, "CoordinateAxis")
            .def(py::init<double, double, double>());
}