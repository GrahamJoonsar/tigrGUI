#include "tigrGUI.hpp"
#include <iostream>

const TPixel BG_COLOR = tigrRGB(255, 255, 255);

int main(void){
    Tigr * screen = tigrWindow(640, 320, "TEST", 0);

    Slider s1(20, 20, 100, 0, 100, 1);
    Slider s2(20, 40, 100, 0, 100, 1);
    Slider s3(20, 60, 100, 0, 100, 1);

    Button b1(20, 100, "PRESS ME");

    int i = 0;

    b1.setFunction({&i}, [](std::vector<void*> args){
        (*static_cast<int*>(args[0]))++;
    });

    std::vector<GUIObject*> guiObjs = {&s1, &s2, &s3, &b1};

    while(!tigrClosed(screen)){
        tigrClear(screen, BG_COLOR);

        for (auto obj : guiObjs){
            obj->draw(screen);
            obj->update(screen);
        }

        tigrPrint(screen, tfont, 200, 20, tigrRGB(127, 127, 127), "%d", i);

        tigrUpdate(screen);
    }
    tigrFree(screen);
}