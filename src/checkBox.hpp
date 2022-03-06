#pragma once

#include "tigr.h"

class CheckBox{
    private:
        int x, y, sideLength;
        bool selected;
        TPixel BG;
        TPixel SELECTED_COLOR;
    public:
        CheckBox(int x, int y, int sideLength){
            this->x = x;
            this->y = y;
            this->sideLength = sideLength;
            this->BG = tigrRGB(200, 200, 200);
            this->SELECTED_COLOR = tigrRGB(50, 255, 128);
            selected = false;
        }

        void draw(Tigr * screen){
            tigrFill(screen, x, y, sideLength, sideLength, BG);
            if (selected) tigrFill(screen, x+2, y+2, sideLength-4, sideLength-4, SELECTED_COLOR);
        }

        void update(Tigr * screen){
            static bool selectedLastFrame = false;
            int mx, my, buttons;
            tigrMouse(screen, &mx, &my, &buttons);

            if ((x < mx) && (mx < x+sideLength) && (y < my) && (my < y+sideLength) && buttons&1 && !selectedLastFrame){
                selected = !selected;
            }

            selectedLastFrame = buttons&1;
        }

        inline bool getVal() const{
            return selected;
        }

};