#!/bin/bash

# CMake will generate the necessarry makefiles or project files with which to compile the program on your system. 

# On Linux-based systems, this will create a makefile inside the build folder.
# On Windows systems, this will create a Visual Studio solution inside the build folder.

# It is important to note that we are not only compiling the sources proprietary to our program,
# but also the GLFW library, which is added through git as a submodule of this repository.

# For this reason, it is necessarry to specify a few options for compiling GLFW:
# GLFW_BUILD_EXAMPLES, GLFW_BUILD_TESTS and GLFW_BUILD_DOCS are all set to OFF.

# This is because we are not interested in building the examples, tests or
# docs for GLFW, we are simply interested in compiling the library binary.

cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S . -B build/

# Once the makefiles or project files have been generated, the program can be compiled.
# CMake can handle the compilation for us, regardless of what method and system is used.

cmake --build build/

# After the binary of the program has been generated, we would like to have it easily
# accessible inside the bin folder, which we create here.

mkdir bin/ &> /dev/null

# Everything in the resources folder will be required to stay alongside the executable for it to work.

cp -r resources/* bin/ &> /dev/null

# This is where the executable itself is copied to the bin folder.
# Below are all the possible locations where it can be found.

cp build/minesweeper bin/ &> /dev/null
cp build/Debug/minesweeper.exe bin/ &> /dev/null
