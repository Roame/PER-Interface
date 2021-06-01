#pragma once

class Texture
{
private:
public:
    char* data;
    int width, height;
    Texture();
    Texture(int width, int height);
    ~Texture(){}
    void setPixel(int x, int y, int r, int g, int b, int a);
};