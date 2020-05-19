#!/usr/bin/env python3

import os

from unittest import TestLoader, TestResult

TEST_CASES_PATH = f"{os.path.dirname(os.path.abspath(__file__))}/test_cases"

if __name__ == "__main__":
    test_loader = TestLoader()
    tests = test_loader.discover(
        start_dir=TEST_CASES_PATH,
        pattern="test*.py"
    )

    test_results = TestResult()
    tests(result=test_results)
