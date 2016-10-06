#!/bin/bash
# A poor man's make script for compiling on Linux and for Windows 
# Author: Derrick Greenspan

gcc src/*.c -o novelOutput.sh -g3 #Linux compile
./bin/compilerSupport/bin/x86_64-w64-mingw32-gcc src/*.c -o novelOutput.exe #Windows compile
cp novelOutput.sh bin/ 
cp novelOutput.exe bin/

read -r -n 1 -s -p "Press any key to continue . . ."
echo
