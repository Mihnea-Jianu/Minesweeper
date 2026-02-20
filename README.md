# Minesweeper

## 

## Windows Dependencies

Make sure the following programs are installed on your computer:

    - Git for Windows (which comes with Git Bash)
    - CMake for Windows
    - Microsoft Visual Studio

## Linux Dependencies

Make sure the following programs are installed on your computer:

    - git
    - bash
    - make
    - cmake
    - xorg-dev
    - libwayland-dev 
    - libxkbcommon-dev 

The last three are development packages necessarry for the compilation of GLFW.

## Installation

**Make sure you have all the dependencies listed for your operating system.**

First, you need to clone this repository to your computer. Make sure to clone recursively, as the repository uses GLFW as a submodule that gets pulled from https://github.com/glfw/glfw.

To do that, open a terminal inside the folder into which to clone the repository and run:

    git clone --recurse-submodules https://github.com/Mihnea-Jianu/Minesweeper

Then, you can simply run the install script, however I encourage you to have a look at exactly what it does:

    ./install.sh

After you have done that, the exectuable as well as all its resources should be inside the bin folder.