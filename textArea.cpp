#include "textArea.hpp"
#include <ctime>

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