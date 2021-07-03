===============================
Adaptive Huffman Coding Library
===============================


About
-----

**libahc** is an implementation of FGK data compression algorithm.
It was written as a part of a small research project and hasn't been
optimized at all, so it **SHOULD NOT** be used in real world projects
(there are many heavily optimized implementations of data compression
algorithms around). Nevertheless it can be usefull for studying purposes, etc.

The source code is hosted on the GitHub: https://github.com/malor/libahc


Author
------

Roman Podoliaka (roman.podolyaka@gmail.com)


Building the library
--------------------

**libahc** uses **CMake** as its build system. The source code is
written in **C++11** so you should have a recent version of your
favourite compiler in order to build the library.

To build the library you should:

1. Change dir to the root of **libahc** source code dir
2. Create a separate build directory and change dir to it: ``mkdir build && cd build``
3. Use **CMake** to create makefiles: ``cmake ..``
4. Run make: ``make``


One can also pass the ``-DBUILD_TESTS=1`` option on step 3 to build the test suite.
The run the test suite use the **run-tests** executable.


License
-------

**libahc** is distributed under GNU Lesser General Public License v3.
See the **LICENSE** file for details.
