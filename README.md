# C++ misc stuff library
**TBD**

## Build
*Requires CMake*
### Release
Run

    mkdir build
    cd build
    cmake ..
    make

to build release version of shared library.

### Debug
Replace

    cmake ..

with

    cmake -DCMAKE_BUILD_TYPE=Debug

to build debug version.

### Documentation
*Requires Doxygen and Graphviz (dot util)*.
Replace

    make

with 

    make doc-libcppmisc

to build html documentation inside build directory.

## Usage
Please refer to `examples` directory to find some use-cases.

### Build
Add `-DBUILD_EXAMPLES=1` to `cmake` command to build examples also.

## License
Licensed under the terms of BSD New License. Copy of license
may be found in LICENSE file.

&copy; Ilya Arefiev <arefiev.id@gmail.com>
