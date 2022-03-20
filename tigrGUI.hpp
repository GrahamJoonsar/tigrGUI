#pragma once
#include "tigr.h"
#include <vector>
#include <string>

class GUIObject{
    public:
        virtual void draw (Tigr*) const = 0;
        virtual void update (Tigr*) = 0;
};

// button.hpp
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

// checkBox.hpp
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

// slider.hpp
class Slider : public GUIObject{
    private:
        static bool selected;
        bool this_selected;
        int x, y, w;
        double min, max;
        double step;
        double current;
        TPixel BG;
        TPixel KNOB_COLOR;

        double clamp(double c) const;

        double roundToStep(double c) const;

    public:
        Slider(int x, int y, int w, double min, double max, double step);
        void draw (Tigr * screen) const;
        void update(Tigr * screen);
        inline double getVal() const {
            return current;
        }
};

// textArea.hpp
class TextArea : public GUIObject{
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
