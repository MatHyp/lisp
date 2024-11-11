#!/bin/bash

exe="my_program"
src="main.cpp src/*.cpp"
flags="-Wall -Wextra -std=c++17 -I./src -g -w"
compile="g++ $src -o $exe $flags"

if [ -f $exe ]; then
    rm $exe
fi

$compile
val=$?

if [ $val -eq 0 ]; then
    ./$exe
    echo ""
fi