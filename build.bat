@echo off
echo Build Start
g++ main.cpp button.cpp textArea.cpp tigr.c -o main -lopengl32 -lgdi32 -lWinmm
echo Build End