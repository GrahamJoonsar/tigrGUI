#include "src/tigr.h"

const TPixel BG_COLOR = tigrRGB(255, 255, 255);

int main(void){
    Tigr * screen = tigrWindow(640, 320, "TEST", 0);
    while(!tigrClosed(screen)){
        tigrClear(screen, BG_COLOR);

        tigrUpdate(screen);
    }
    tigrFree(screen);
}