# Minesweeper

## Linux Installation

First, make sure the following programs are installed on your computer:

- git
- make
- cmake
- xorg-dev
- libwayland-dev 
- libxkbcommon-dev 

The last three are necessarry for the compilation of GLFW.

Next, you need to clone this repository to your computer. Make sure to clone recursively, as the project uses GLFW as a submodule that gets pulled from https://github.com/glfw/glfw.

To do that, open a terminal inside the folder into which to clone the repository and run:

    git clone --recurse-submodules https://github.com/Mihnea-Jianu/Minesweeper

Then, you can simply run the install script, however I encourage you to have a look at exactly what it does:

    ./install.sh
