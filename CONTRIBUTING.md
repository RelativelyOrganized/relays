CONTRIBUTING
============

## Installation

Relays is (as of yet) not dependent on any external library, except for the Python headers and a C++17 compliant compiler. To build it, do as follows:

```bash
mkdir build && cd build
cmake ..
make -j$(nproc) && sudo make install
sudo ldconfig  # only necessary the first time to register the library
```

### Python

Given that the Python header files are installed on the system, a Python wrapper for **Relays** will be built along the C++ library. This wrapper is needed for the most advanced uses of this tool.

Once built and installed, you can get information about what's available as follows:

```python
import pyrelays

help(pyrelays)
```

## Coding style

We use LLVM style for the C++ code, with a few exceptions. See the [clang-format configuration](./.clang-format) for more about this.

It is possible to let git ensure that you are conforming to the standards by using pre-commit hooks and clang-format:
```
sudo apt-get install clang-format exuberant-ctags
# Then in Relays' home folder:
rm -rf $(pwd)/.git/hooks && ln -s $(pwd)/.hooks $(pwd)/.git/hooks
```

## Test coverage

Coverage testing relies on [lcov](http://ltp.sourceforge.net/coverage/lcov.php), so make sure to have it installed beforehand.

To check the coverage, you need to build Relays with a specific flag, as follows:

```bash
mkdir -p build && cd build && rm -rf *
cmake -DTEST_COVERAGE=ON ..
make -j4
```

You can then test the coverage:

```bash
make check_coverage
```
