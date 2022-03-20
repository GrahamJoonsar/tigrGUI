#pragma once
#include "tigr.h"
#include <vector>
#include <string>
#include "guiObject.hpp"

class Button : public GUIObject{
    private:
        int x, y, w, h;
        int borderWidth;
        bool selected = false;
        TPixel currentBGColor;
        TPixel highlightedColor;
        TPixel bgColor;
        TPixel borderColor;
        TPixel textColor;
        std::string label;
        std::vector<void*> args;
        void (*f)(std::vector<void*>);
    public:
        Button(int x, int y, std::string label);
        void draw(Tigr * screen) const;
        void update(Tigr* screen);
        void setFunction(std::vector<void*> args, void(*g)(std::vector<void*>));
        void setPos(int x, int y);
        void setText(std::string newText);
        void setTextWithoutDimensions(std::string newText);
        void setDimensions(int w, int h);
};