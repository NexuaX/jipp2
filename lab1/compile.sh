#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: compile.sh [file to compile]"
    echo "Compiles specified file to bin directory"
    exit
fi

if [ ! -d './bin' ]; then
    echo `mkdir bin`
fi

if [ -f $1 ]; then
    FILENAME=${1//.cpp}
    echo `g++ -std=c++11 $1 -o bin/$FILENAME`
    echo -e "\e[33;1mCompiled!"
    exit
else
    echo
    echo -e "File $1 do \e[1;31mnot \e[12;39mexist!"
    exit
fi
