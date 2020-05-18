from pyrelays import Clock
from unittest import TestCase


class ClockTestCase(TestCase):
    def test_clock(self):
        clock = Clock()
        self.assert_equal(clock.frequency, 100.0)
        clock.set_frequency(50.0)
        self.assert_equal(clock.frequency, 50.0)
        clock.set_period(0.01)
        self.assert_equal(clock.frequency, 100.0)
