//
// Created by tom on 03/03/23.
//
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include "Interpolator.h"
#include "RGIThreads.h"

namespace py = pybind11;

void initInterp3D(py::module_& m)
{
    py::class_<Interpolator3D<double, double, double, Linear, double>>(m, "LinearInterpolator3D")
        .def(py::init<CoordinateAxis<double>, CoordinateAxis<double>, CoordinateAxis<double>, Grid3D<double, Linear>>())
        .def("interpolate", [](
                const Interpolator3D<double, double, double, Linear, double>& interpolator,
                const py::array_t<double>& x,
                const py::array_t<double>& y,
                const py::array_t<double>& z
            ){
            auto size = x.size();
            auto result = py::array_t<double>(py::array::ShapeContainer{size});
            auto _x = x.template unchecked<1>();
            auto _y = y.template unchecked<1>();
            auto _z = z.template unchecked<1>();
            auto _result = result.template mutable_unchecked<1>();
            {
                py::gil_scoped_release release;
                dispatch(
                    [&](size_t start, size_t end) {
                        for (size_t i=start; i<end; ++i) {
                            _result(i) = interpolator.interpolate(_x(i), _y(i), _z(i));
                        }
                    }, size, 0);
            }

            return result;
        });
}