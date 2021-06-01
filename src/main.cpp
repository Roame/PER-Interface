#include <iostream>
// #include <fstream>

#include "graphics/GraphicsManager.h"
#include "math/Matrix2D.h"
#include "graphics/Texture.h"

int main(int argc, char **argv) {
    GraphicsManager graphics(argc, argv);

    int width = 1024, height = 768;

    Texture tex(width, height);
    std::cout << tex.width << " " << tex.height << std::endl;

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            int val = (int) (((float)i/(width-1)+(float)j/(height-1))/2*255);
            tex.setPixel(i, j, 0, val, 0, 255);
        }
    }

    graphics.loadTexture(tex);

    while(1){
        graphics.update();
    }
}