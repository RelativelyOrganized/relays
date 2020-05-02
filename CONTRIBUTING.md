CONTRIBUTING
============

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
