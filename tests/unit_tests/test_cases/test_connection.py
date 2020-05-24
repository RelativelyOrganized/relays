from pyrelays import Connection
from unittest import TestCase


class ConnectionTestCase(TestCase):
    def test_connection(self):
        connection = Connection()
        self.assert_equal(connection.src, 0)
        self.assert_equal(connection.to, 0)
        self.assert_equal(connection.layoutIn, 0)
        self.assert_equal(connection.layoutOut, 0)
        self.assert_equal(connection.source, Connection.Source.Relay)
        self.assert_equal(connection.sink, Connection.Sink.Relay)
        self.assert_equal(connection.slot, Connection.Slot.Input)
        self.assert_equal(connection.invert, False)
