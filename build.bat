@echo off
echo Build Start
g++ main.cpp tigr.c tigrGUI.cpp -o main -lopengl32 -lgdi32 -lWinmm
echo Build End