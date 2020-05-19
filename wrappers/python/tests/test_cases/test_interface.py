from pyrelays import Interface
from unittest import TestCase


class InterfaceTestCase(TestCase):
    def test_interface(self):
        interface = Interface()
        self.assert_equal(interface.index, 0)
        self.assert_equal(interface.slot, Interface.Slot.Input)
        self.assert_equal(interface.index, Interface.Source.Relay)
