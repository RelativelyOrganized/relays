from perf_test import RelaysTestCase
from pyrelays import Simulation
from time import sleep


class SimulationTestCase(RelaysTestCase):
    def test(self):
        simulation: Simulation = Simulation()
        simulation.run(int(1e8))
        while simulation.is_running():
            sleep(0.001)
        simulation.stop()
