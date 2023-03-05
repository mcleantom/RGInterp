#include <pybind11/pybind11.h>
#include <iostream>
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

void initAxis(py::module_& m);
void initInterp3D(py::module_& m);
void initGrid(py::module_& m);

PYBIND11_MODULE(_core, m) {
    m.def("hi", [](){std::cout << "hi" << std::endl;});
    initAxis(m);
    initGrid(m);
    initInterp3D(m);
#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}