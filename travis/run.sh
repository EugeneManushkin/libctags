#!/bin/bash

echo "Preved-medved"

mkdir build && cd build
cmake ..
make
./mytest
