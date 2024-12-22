#include "tlsh.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/function.h>
#include <nanobind/stl/list.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include <string>

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(_tlsh, m)
{
    m.doc()               = "The native `tlsh` module";
    m.attr("__version__") = "0.1.0";
    nb::class_<Tlsh>(m, "Tlsh", "Class Tlsh")
        .def(nb::init<>())
        .def("reset", &Tlsh::reset)
        .def("update", nb::overload_cast<std::vector<u8> const &>(&Tlsh::update))
        .def("final", &Tlsh::final)
        .def("getHashString", &Tlsh::getHashString)
        .def("getHashBytes", &Tlsh::getHashBytes)
        .def("isValid", &Tlsh::isValid)
        .def("totalDiff", &Tlsh::totalDiff)
        .def("fromTlshStr", &Tlsh::fromTlshStr)
        .def("fromTlshBytes", &Tlsh::fromTlshBytes)
        .def_ro_static("version", &Tlsh::version)
        .def_ro_static("version_info", &Tlsh::version_info);
}
