#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>

#include "./clock.h"
#include "./connection.h"
#include "./layout.h"
#include "./relay.h"
#include "./simulation.h"

using namespace Relays;
namespace py = pybind11;

PYBIND11_MODULE(pyrelays, m)
{
    m.doc() = R"pbdoc(
        Python wrapper for Relays
        -------------------------

        .. currentmodule:: relays

        .. autosummary::
            :toctree: _generate
            
    )pbdoc";

    /**
     * Relay
     */
    py::class_<Relay>(m, "Relay")
        .def(py::init<>())
        .def_readwrite("switch_duration", &Relay::switchDuration);

    /**
     * Clock
     */
    py::class_<Clock>(m, "Clock")
        .def(py::init<>())
        .def("set_frequency", &Clock::setFrequency)
        .def("set_period", &Clock::setPeriod)
        .def_readonly("frequency", &Clock::frequency)
        .def_readonly("period", &Clock::period);

    /**
     * Connection
     */
    py::class_<Connection> connection(m, "Connection");
    connection.def(py::init<>())
        .def_readwrite("src", &Connection::from)
        .def_readwrite("to", &Connection::to)
        .def_readwrite("layout_in", &Connection::layoutIn)
        .def_readwrite("layout_out", &Connection::layoutOut)
        .def_readwrite("source", &Connection::source)
        .def_readwrite("sink", &Connection::sink)
        .def_readwrite("slot", &Connection::slot)
        .def_readwrite("invert", &Connection::invert);

    py::enum_<Connection::Slot>(connection, "Slot")
        .value("Input", Connection::Slot::Input)
        .value("Command", Connection::Slot::Command)
        .export_values();

    py::enum_<Connection::Source>(connection, "Source")
        .value("Relay", Connection::Source::Relay)
        .value("Clock", Connection::Source::Clock)
        .value("Layout", Connection::Source::Layout)
        .export_values();

    py::enum_<Connection::Sink>(connection, "Sink")
        .value("Relay", Connection::Sink::Relay)
        .value("Layout", Connection::Sink::Layout)
        .export_values();

    /**
     * Interface
     */
    py::class_<Interface> interface(m, "Interface");
    interface.def(py::init<>())
        .def_readwrite("index", &Interface::index)
        .def_readwrite("slot", &Interface::slot)
        .def_readwrite("source", &Interface::source);

    py::enum_<Interface::Slot>(interface, "Slot")
        .value("Input", Interface::Slot::Input)
        .value("Command", Interface::Slot::Command);

    py::enum_<Interface::Source>(interface, "Source")
        .value("Relay", Interface::Source::Relay)
        .value("Clock", Interface::Source::Clock)
        .value("Layout", Interface::Source::Layout);

    /**
     * Layout
     */
    py::class_<Layout>(m, "Layout")
        .def(py::init<>())
        .def("add_layout", &Layout::addLayout)
        .def_readwrite("children_layout", &Layout::_childrenLayouts)
        .def_readwrite("relays", &Layout::_childrenLayouts)
        .def_readwrite("clocks", &Layout::_clocks)
        .def_readwrite("connections", &Layout::_connections)
        .def_readwrite("interface_in", &Layout::_interfaceIn)
        .def_readwrite("interface_out", &Layout::_interfaceOut);

    /**
     * Simulation
     */
    py::class_<Simulation>(m, "Simulation")
        .def(py::init<>())
        .def("is_running", &Simulation::isRunning)
        .def("run", (bool (Simulation::*)(uint64_t)) & Simulation::run, py::arg("time_limit") = 0)
        .def("stop", &Simulation::stop)
        .def("set_layout", &Simulation::setLayout)
        .def("set_step_period", &Simulation::setStepPeriod);
}
