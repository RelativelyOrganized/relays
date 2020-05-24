Relays
======

![CI](https://github.com/RelativelyOrganized/relays/workflows/CI/badge.svg?branch=develop)

Relays (codename) is a simulation software which goal is to allow for building virtual electronic device from the ground up. What this mean is that the base building block are relays, and that an electronic circuit is simulated from a description of the connections between some (sometimes a lot) of them.

The goals of this project are mostly educational:

* understand more how complex electronic circuit work (logically) by designing them
* have a good reason to apply data-driven development to real-world code


Preliminary architecture
------------------------

The following classes are involved at runtime, during a simulation:

* **Transistor**: base element for any circuit, currently merely a struct holding info about its status (command input, data input, data output and inverted data output).
* **Wire**: a basic structure describing a connection from a **Transistor** output to another one's input.
* **Quartz**: gives the pace for the circuit to run.
* **Circuit**: a collection of **Transistors** and **Wires** which together describe a more or less complexe virtual circuit.
* **Traverser**: object which applies a clock cycle to a **Circuit**, and updates its **Relays** states accordingly.
* **Simulation**: object which drives the **Traverser**, in particular its time resolution.

On top of that exists an intermediate representation of the system which is converted to a **Circuit** before running the simulation:
* **Relay**: translates to a **Transistor** at runtime.
* **Connection**: translates to a **Wire** at runtime.
* **Clock**: translates to a **Quartz** at runtime.
* **Layout**: translates to a **Circuit** at runtime.
