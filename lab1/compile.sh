#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: ./compile.sh [file to compile]"
    echo "Compiles specified file to bin directory"
    exit
fi

if [ ! -d './bin' ]; then
    echo `mkdir bin`
fi

if [ -f $1 ]; then
    FILENAME=${1//.cpp}
    echo `g++ -std=c++11 $1 -o bin/$FILENAME`
    echo "Compiled!"
    exit
else
    echo "File $1 do not exist!"
    exit
fi
