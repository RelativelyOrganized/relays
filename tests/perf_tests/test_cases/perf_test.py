import os

from time import time
from typing import Type
from unittest import TestCase


class RelaysTestCase(TestCase):
    test_dir = os.path.dirname(os.path.realpath(__file__))

    def __init__(self, *args, **kwargs) -> None:
        super().__init__(*args, **kwargs)
        self.start_time: float = 0.0

    @classmethod
    def setUpClass(cls: Type['RelaysTestCase']) -> None:
        print(f"{os.path.basename(__file__):<16}\t", end='')
        cls.start_time = time()

    @classmethod
    def tearDownClass(cls: Type['RelaysTestCase']) -> None:
        total_duration_ms: float = (time() - cls.start_time) * 1000.0
        print(f" {total_duration_ms:.3f}ms")
