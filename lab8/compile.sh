#!/bin/bash

if [[ $# -eq 1 && $1 == "--help" ]]; then
    echo "Usage: compile.sh"
    echo "Creates build dir, CMake's and then Make's the lab8 output"
    exit
fi

if [ ! -d './build' ]; then
    echo `mkdir build`
fi

if [[ -f "CMakeLists.txt" ]]; then
    echo -e "\e[1;34mexecuting: \e[39;22m cmake -B build"
    cmake -B build
    if [ $? -eq 0 ]; then
        echo -e "\e[33;1mCmake done!"
    else 
        echo -e "\e[35;1mErrors (Cmake)!"
        exit
    fi
    echo -e "\e[1;34mexecuting: \e[39;22m make -C build"
    make -C build
    if [ $? -eq 0 ]; then
        echo -e "\e[33;1mCompiled!"
        echo -e "\e[33;22mBinary: ./build/output"
    else 
        echo -e "\e[35;1mErrors!"
    fi
    exit
else
    echo
    echo -e "File CMakeLists.txt do \e[1;31mnot \e[12;39mexist!"
    exit
fi