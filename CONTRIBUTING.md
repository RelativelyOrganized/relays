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
