#pragma once

#include "tigr.h"
#include "guiObject.hpp"

class CheckBox : public GUIObject{
    private:
        int x, y, sideLength;
        bool selected;
        TPixel BG;
        TPixel SELECTED_COLOR;
    public:
        CheckBox(int x, int y, int sideLength);

        void draw(Tigr * screen) const;

        void update(Tigr * screen);

        inline bool getVal() const{
            return selected;
        }

};