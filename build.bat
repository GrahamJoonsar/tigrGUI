@echo off
echo Build Start
g++ main.cpp  src/tigr.c -o main -lopengl32 -lgdi32 -lWinmm
echo Build End