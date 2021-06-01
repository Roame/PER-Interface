#pragma once

#include "Texture.h"

class GraphicsManager
{
private:
    Texture tex;
public:
    GraphicsManager(int argc, char **argv);
    ~GraphicsManager();
    void update();
    void loadTexture(Texture texture);
};