#pragma once
#include "tigr.h"
#include <vector>
#include <string>

class Button{
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
        void (*f)(std::vector<void*>);
    public:
        Button(int x, int y, std::string label);
        void draw(Tigr * screen) const;
        void update(Tigr* screen, std::vector<void*> args);
        void setFunction(void(*g)(std::vector<void*>));
        void setPos(int x, int y);
        void setText(std::string newText);
        void setTextWithoutDimensions(std::string newText);
        void setDimensions(int w, int h);
};