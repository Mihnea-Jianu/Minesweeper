#!/bin/sh

cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S . -B build/
cmake --build build/

mkdir bin/

cp -r build/minesweeper resources/sprites/ resources/settings.txt resources/personal_best.txt bin/
