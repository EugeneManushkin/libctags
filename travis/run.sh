#!/bin/bash

echo "Preved-medved"

mkdir build && cd build
cmake ..
make
test/mytest
