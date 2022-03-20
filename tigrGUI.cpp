#include "tigrGUI.hpp"
#include <ctime>

// button.cpp
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

void Button::update(Tigr * screen){
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

void Button::setFunction(std::vector<void*> args, void(*g)(std::vector<void*>)){
    this->args = args;
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

// checkBox.cpp
CheckBox::CheckBox(int x, int y, int sideLength){
    this->x = x;
    this->y = y;
    this->sideLength = sideLength;
    this->BG = tigrRGB(200, 200, 200);
    this->SELECTED_COLOR = tigrRGB(50, 255, 128);
    selected = false;
}

void CheckBox::draw(Tigr * screen) const{
    tigrFill(screen, x, y, sideLength, sideLength, BG);
    if (selected) tigrFill(screen, x+2, y+2, sideLength-4, sideLength-4, SELECTED_COLOR);
}

void CheckBox::update(Tigr * screen){
    static bool selectedLastFrame = false;
    int mx, my, buttons;
    tigrMouse(screen, &mx, &my, &buttons);

    if ((x < mx) && (mx < x+sideLength) && (y < my) && (my < y+sideLength) && buttons&1 && !selectedLastFrame){
        selected = !selected;
    }

    selectedLastFrame = buttons&1;
}

// slider.cpp
bool Slider::selected = false;
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

// textArea.cpp
TextArea::TextArea(int x, int y, int textWidth, int textHeight){
    this->x = x;
    this->y = y;
    this->cwidth = tigrTextWidth(tfont, "M");
    this->cheight = tigrTextHeight(tfont, "M");
    this->w = cwidth*textWidth+10;
    this->h = cheight*textHeight+5;
    this->twidth = textWidth;
    this->theight = textHeight;

    this->borderWidth = 2;

    this->bgColor = tigrRGB(200, 200, 200);
    this->textColor = tigrRGB(255, 255, 255);
    this->borderColor = tigrRGB(100, 100, 100);
}

void TextArea::draw(Tigr * screen) const {
    tigrFill(screen, x, y, w, h, borderColor);
    tigrFill(screen, x+borderWidth, y+borderWidth,
            w-2*borderWidth, h-2*borderWidth, bgColor);
    // Drawing text
    std::string formattedText = "";
    for (int i = 0; i < text.length(); i++){
        if (i%twidth == 0 && i != 0) formattedText += '\n';
        formattedText += text[i];
    }
    if (cursorOn) formattedText += '|'; // blinking cursor
    tigrPrint(screen, tfont, x+5, y+4, textColor, formattedText.c_str());
}

void TextArea::update(Tigr * screen){
    static time_t lastTime = std::time(0);
    int mx, my, buttons;
    tigrMouse(screen, &mx, &my, &buttons);
    if (buttons & 1) this_selected = (x < mx && mx < x+w) && (y < my && my < y+h);

    // This text box is able to be typed in
    if (this_selected){
        // Text input //
        char input = tigrReadChar(screen);
        if (input){
            if (input == 8){ // BACKSPACE
                if (text.length() > 0) text.pop_back();
            } else if (text.length() < twidth*theight){
                text += input;
            }
        }

        // Blinking Cursor //
        const time_t currentTime = std::time(0);
        if (currentTime-lastTime == 1){
            cursorOn = true;
        } else { 
            cursorOn = false;
            lastTime = currentTime;
        }
    }
}