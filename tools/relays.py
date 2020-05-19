#!/usr/bin/env python3

import signal

from pyrelays import Simulation
from time import sleep

exit: bool = False


def sig_handler(signo, stack_frame):
    global exit
    exit = True


if __name__ == "__main__":
    signal.signal(signal.SIGTERM, sig_handler)
    signal.signal(signal.SIGINT, sig_handler)

    simulation: Simulation = Simulation()
    print("Running a default (empty...) circuit")
    simulation.run()

    while exit is not True:
        sleep(0.1)

    print("Stopping the simulation...")
    simulation.stop()
    print("Simulation stopped")

