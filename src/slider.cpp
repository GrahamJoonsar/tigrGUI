#include "slider.hpp"

double Slider::clamp(double c) const {
    if (c < min) return min;
    if (c > max) return max;
    return c;
}

double Slider::roundToStep(double c) const {
    double less = (int)(c/step) * step;
    double more = (int)(c/step + 1) * step;
    return more - c < c - less ? more : less;
}

Slider::Slider(int x, int y, int w, double min, double max, double step){
    this->x = x;
    this->y = y;
    this->w = w;

    this->max = max;
    this->min = min;
    this->step = step;

    this->current = roundToStep((min+max)/2);
    this_selected = false;

    BG = tigrRGB(150, 150, 150);
    KNOB_COLOR = tigrRGB(200, 200, 255);
}

void Slider::draw(Tigr * screen) const {
    tigrFill(screen, x+2, y+1, w-2, 9, BG);
    tigrFillCircle(screen, x+(w*((current-min)/(max-min))), y+5, 7, KNOB_COLOR);
}

void Slider::update(Tigr * screen){
    int mx, my, buttons;
    tigrMouse(screen, &mx, &my, &buttons);
    if (buttons & 1){
        if ((x < mx) && (mx < x+w) && (y < my) && (my < y+9) && !selected){
            selected = this_selected = true;
        }
    } else selected = this_selected = false;

    if (this_selected) current = roundToStep(clamp(((mx-x) / (double)w) * (max-min) + min));
}