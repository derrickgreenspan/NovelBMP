@echo off
REM A poor man's Batch Script for compiling natively on Windows
REM Author: Derrick Greenspan

REM Specify the location of MinGW  by modifying PATH
set PATH=%PATH%;bin\winCompilerSupport\MinGW\bin\

bin\winCompilerSupport\MinGW\bin\mingw32-gcc.exe src\*.c -o novelOutput.exe      

pause
