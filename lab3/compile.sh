#!/bin/bash

if [[ $# -eq 1 && $1 == "--help" ]]; then
    echo "Usage: compile.sh"
    echo "Compiles lab3 to bin directory"
    exit
fi

if [ ! -d './bin' ]; then
    echo `mkdir bin`
fi

if [[ -f "zad.cpp" && -f "matrix.cpp" ]]; then
    echo `g++ -std=c++11 -c matrix.cpp -o matrix.o`
    echo `g++ -std=c++11 zad.cpp matrix.o -o bin/zad`
    echo -e "\e[33;1mCompiled!"
    exit
else
    echo
    echo -e "File(s) do \e[1;31mnot \e[12;39mexist!"
    exit
fi
