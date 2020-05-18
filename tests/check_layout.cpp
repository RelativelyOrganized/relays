#undef NDEBUG // get assert in release mode

#include <cassert>
#include <iostream>

#include "./layout.h"

using namespace Relays;

/*
 * This generates a simple layout that has:
 *
 * - two relays
 * - one clock
 * - two input pins
 * - one output pin
 *
 * and looks like this:
 *
 *      +--------------------------------------+
 *      |   +-----+                  +-----+   |
 * In 0 >~~~|Relay|----------------->|Relay|~~~> Out 0
 * In 1 >~~~|0    |     +-----+  +-->|1    |   |
 *      |   +-----+     |Clock|--+   +-----+   |
 *      |               |0    |                |
 *      |               +-----+                |
 *      +--------------------------------------+
 *
 * legend:
 * ~~~ interface
 * --- connection
 *
 */
Layout createLayout()
{
    Layout layout;

    layout._relays.resize(2);
    layout._clocks.resize(1);
    layout._connections.resize(2);
    layout._interfaceIn.resize(2);
    layout._interfaceOut.resize(1);

    auto& connections = layout._connections;
    connections[0].from = 0;
    connections[0].to = 1;
    connections[1].from = 0;
    connections[1].to = 1;
    connections[1].source = Source::Clock;
    connections[1].sink = Sink::Relay;

    auto& interfaceIn_1 = layout._interfaceIn[0];
    auto& interfaceIn_2 = layout._interfaceIn[1];
    interfaceIn_1.index = 0;
    interfaceIn_1.slot = Slot::Input;
    interfaceIn_2.index = 0;
    interfaceIn_2.slot = Slot::Command;

    auto& interfaceOut = layout._interfaceOut[0];
    interfaceOut.index = 1;

    return layout;
}

void testSimpleLayout()
{
    auto layout = createLayout();

    auto flatLayout = layout.flatten();
    assert(flatLayout._childrenLayouts.size() == layout._childrenLayouts.size());
    assert(flatLayout._relays.size() == layout._relays.size());
    assert(flatLayout._connections.size() == layout._connections.size());
    assert(flatLayout._clocks.size() == layout._clocks.size());
    assert(flatLayout._interfaceIn.size() == layout._interfaceIn.size());
    assert(flatLayout._interfaceOut.size() == layout._interfaceOut.size());
}

void testChildLayout()
{
    auto layout = createLayout();
    auto childLayout = createLayout();

    Connection inputConnection;
    inputConnection.from = 0;
    inputConnection.to = 0;
    inputConnection.source = Source::Relay;
    inputConnection.sink = Sink::Layout;
    inputConnection.invert = true;

    Connection outputConnection;
    outputConnection.from = 0;
    outputConnection.to = 1;
    outputConnection.source = Source::Layout;
    outputConnection.sink = Sink::Relay;

    layout.addLayout(childLayout, {inputConnection}, {outputConnection});
    assert(layout._childrenLayouts.size() == 1);
    assert(layout._relays.size() == 2);
    assert(layout._connections.size() == 4);

    auto flatLayout = layout.flatten();

    // Check that all elements are there
    assert(flatLayout._relays.size() == 4);
    assert(flatLayout._clocks.size() == 2);
    assert(flatLayout._connections.size() == 6);
    assert(flatLayout._interfaceIn.size() == 2);
    assert(flatLayout._interfaceOut.size() == 1);

    // Check that connections are correct
    auto& connections = flatLayout._connections;
    assert(connections[0].from == 0);
    assert(connections[0].to == 1);
    assert(connections[0].source == Source::Relay);
    assert(connections[0].sink == Sink::Relay);

    assert(connections[1].from == 0);
    assert(connections[1].to == 1);
    assert(connections[1].source == Source::Clock);
    assert(connections[1].sink == Sink::Relay);

    assert(connections[2].from == 0);
    assert(connections[2].to == 2);
    assert(connections[2].source == Source::Relay);
    assert(connections[2].sink == Sink::Relay);

    assert(connections[3].from == 3);
    assert(connections[3].to == 1);
    assert(connections[3].source == Source::Relay);
    assert(connections[3].sink == Sink::Relay);

    assert(connections[4].from == 2);
    assert(connections[4].to == 3);
    assert(connections[4].source == Source::Relay);
    assert(connections[4].sink == Sink::Relay);

    assert(connections[5].from == 1);
    assert(connections[5].to == 3);
    assert(connections[5].source == Source::Clock);
    assert(connections[5].sink == Sink::Relay);

    // And now, check interfaces
    auto& in = flatLayout._interfaceIn;
    assert(in[0].index == 0);
    assert(in[0].slot == Slot::Input);
    assert(in[1].index == 0);
    assert(in[1].slot == Slot::Command);

    auto& out = flatLayout._interfaceOut;
    assert(out[0].index == 1);
}

int main()
{
    testSimpleLayout();
    testChildLayout();

    return 0;
}
