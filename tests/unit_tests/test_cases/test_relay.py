from pyrelays import Relay
from unittest import TestCase


class RelayTestCase(TestCase):
    def test_relay(self):
        relay = Relay()
        self.assert_equal(relay.switch_duration, 0)
        relay.switch_duration = 5
        self.assert_equal(relay.switch_duration, 5)
