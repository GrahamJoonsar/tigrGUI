#include "tigr.h"
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include<iostream>
 
float interpolate(float a0, float a1, float w) {
    /* // You may want clamping by inserting:
     * if (0.0 > w) return a0;
     * if (1.0 < w) return a1;
     */
    return (a1 - a0) * w + a0;
    /* // Use this cubic interpolation [[Smoothstep]] instead, for a smooth appearance:
     * return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
     *
     * // Use [[Smootherstep]] for an even smoother result with a second derivative equal to zero on boundaries:
     * return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
     */
}

typedef struct {
    float x, y;
} vector2;

/* Create pseudorandom direction vector
 */
vector2 randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix, b = iy;
    a *= 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    vector2 v;
    v.x = cos(random); v.y = sin(random);
    return v;
}

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(int ix, int iy, float x, float y) {
    // Get gradient from integer coordinates
    vector2 gradient = randomGradient(ix, iy);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx*gradient.x + dy*gradient.y);
}

// Compute Perlin noise at coordinates x, y
float perlin(float x, float y) {
    // Determine grid cell coordinates
    int x0 = (int)floor(x);
    int x1 = x0 + 1;
    int y0 = (int)floor(y);
    int y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Interpolate between grid point gradients
    float n0, n1, ix0, ix1, value;

    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);
    return value;
}
const TPixel BG_COLOR = tigrRGB(255, 255, 255);

TPixel getColor(double n){
    if (n < 25){
        return tigrRGB(50, 128, 255);
    } else if (n < 40){
        return tigrRGB(188, 154, 134);
    }else if (n < 50){
        return tigrRGB(200, 200, 200);
    }
     else {
        return tigrRGB(50, 255, 128);
    }
}



int main(void){
    Tigr * screen = tigrWindow(640, 320, "TEST", 0);
    
    int xoff = 0;
    int yoff = 0;

    int speed = 10;

    while(!tigrClosed(screen)){
        tigrClear(screen, BG_COLOR);
        for (int y = 0; y < screen->h; y++){
            for (int x = 0; x < screen->w; x++){
                const double i = (double)(y+yoff)*5/screen->h;
                const double j = (double)(x+xoff)*6/screen->w;

                double n = floor(perlin(j, i)*255);

                screen->pix[y*screen->w + x] = getColor(n);
            }
        }
        if (tigrKeyHeld(screen, TK_RIGHT)){
            xoff+=speed;
        } else if (tigrKeyHeld(screen, TK_LEFT)){
            xoff-=speed;
        }

        if (tigrKeyHeld(screen, TK_UP)){
            yoff-=speed;
        } else if (tigrKeyHeld(screen, TK_DOWN)){
            yoff+=speed;
        }

        tigrUpdate(screen);
    }
    tigrFree(screen);
}