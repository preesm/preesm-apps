@echo off
mkdir bin
cd bin
cmake ..\ -G "Visual Studio 16 2019" -A Win32
pause