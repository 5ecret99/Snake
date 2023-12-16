#!/bin/bash
mkdir -p build
cd build 
cmake -S ../src/
make
mkdir -p ../bin
mv main ../bin/
cd ..
