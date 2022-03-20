#pragma once

#include "tigr.h"
#include "guiObject.hpp"
#include <string>

class TextArea : GUIObject{
    private:
        int x, y, w, h;
        int borderWidth;
        int twidth, theight, cwidth, cheight;
        bool this_selected = false;
        bool cursorOn = false;
        std::string text;
        TPixel bgColor;
        TPixel borderColor;
        TPixel textColor;
    public:
        TextArea(int x, int y, int textWidth, int textHeight);
        void draw(Tigr * screen) const;
        void update(Tigr * screen);

        inline std::string getText() const {
            return text;
        }
};