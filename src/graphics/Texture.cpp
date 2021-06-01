#include "Texture.h"

#include <iostream>

Texture::Texture():
width(0), height(0), data(new char[0]){
}

Texture::Texture(int width, int height):
width(width),height(height), data(new char[width*height*4]{0}){}

void Texture::setPixel(int x, int y, int r, int g, int b, int a){
    if(x >= width) { throw "x is out of bounds"; return; }
    if(y >= height) { throw "y is out of bounds"; return; }
    int index = 4*(x+y*width);
    data[index] = r;
    data[index+1] = g;
    data[index+2] = b;
    data[index+3] = a;
}