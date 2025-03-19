# graph.cpp

**Note**: Requires C++20 or newer.

### Build process

1. Clone the repository
2. cd graph.cpp
3. mkdir -p build
4. cd build
5. cmake ..
6. cmake --build .

To set the compiler (for instance, if your system default G++ version does not support C++20), you can set environment variables:

```bash
$ export CXX=g++-11
$ export CC=gcc-11
```

### Run tests

First, follow the build process.

1. cd build
2. ./test_graph
