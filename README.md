Relays
======

Relays (codename) is a simulation software which goal is to allow for building virtual electronic device from the ground up. What this mean is that the base building block are relays, and that an electronic circuit is simulated from a description of the connections between some (sometimes a lot) of them.

The goals of this project are mostly educational:

* understand more how complex electronic circuit work (logically) by designing them
* have a good reason to apply data-driven development to real-world code


Preliminary architecture
------------------------

* a parser/lexer: read the configuration
* a graph optimizer: organize relays configuration in memory to match their relationship
* a traverser: apply a clock cycle to the configuration and update the relays accordingly
* a way to set inputs and read outputs
