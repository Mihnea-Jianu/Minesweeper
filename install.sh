#!/bin/sh

sudo apt update
sudo apt install libwayland-dev libxkbcommon-dev xorg-dev

cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S . -B build/

mkdir bin

cd build

make

cp -r minesweeper ../resources/sprites ../resources/settings.txt ../resources/personal_best.txt ../bin
