#!/bin/bash

if [[ $# -eq 1 && $1 == "--help" ]]; then
    echo "Usage: compile.sh"
    echo "Creates build dir, CMake's and then Make's the lab4 binary"
    exit
fi

if [ ! -d './build' ]; then
    echo `mkdir build`
fi

if [[ -f "CMakeLists.txt" ]]; then
    echo `cmake -B build`
    echo `make -C build`
    echo -e "\e[33;1mCompiled!"
    exit
else
    echo
    echo -e "File CMakeLists.txt do \e[1;31mnot \e[12;39mexist!"
    exit
fi