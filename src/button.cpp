#include "button.hpp"

Button::Button(int x, int y, std::string label){
    this->x = x;
    this->y = y;
    this->w = tigrTextWidth(tfont, label.c_str())+10;
    this->h = tigrTextHeight(tfont, label.c_str())+5;

    this->borderWidth = 2;

    this->label = label;

    this->bgColor = tigrRGB(255, 100, 100);
    this->textColor = tigrRGB(255, 255, 255);
    this->borderColor = tigrRGB(100, 100, 100);
    this->currentBGColor = bgColor;
    this->highlightedColor = tigrRGB(bgColor.r-50, bgColor.g-50, bgColor.b-50);

    this->f = nullptr;
}

void Button::draw(Tigr * screen) const {
    tigrFill(screen, x, y, w, h, borderColor);
    tigrFill(screen, x+borderWidth, y+borderWidth,
            w-2*borderWidth, h-2*borderWidth, currentBGColor);
    tigrPrint(screen, tfont, x+5, y+4, textColor, label.c_str());
}

void Button::update(Tigr * screen, std::vector<void*> args){
    int mx, my, buttons;
    tigrMouse(screen, &mx, &my, &buttons);
    // On the button
    if (((x < mx) && (mx < x+w)) && ((y < my) && (my < y+h))){
        currentBGColor = highlightedColor;
        // Clicked button
        if ((buttons & 1) && !selected) {
            f(args);
            selected = true;
        } else if (!(buttons & 1)) selected = false;
    } else currentBGColor = bgColor;
}

void Button::setFunction(void(*g)(std::vector<void*>)){
    f = g;
}

void Button::setPos(int x, int y){
    this->x = x;
    this->y = y;
}

void Button::setText(std::string newText){
    this->label = newText;
    this->w = tigrTextWidth(tfont, newText.c_str())+10;
    this->h = tigrTextHeight(tfont, newText.c_str())+5;
}

void Button::setTextWithoutDimensions(std::string newText){
    this->label = newText;
}

void Button::setDimensions(int w, int h){
    this->w = w;
    this->h = h;
}