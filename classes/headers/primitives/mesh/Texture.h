#pragma once
#include <SDL2/SDL.h>
#include "../../math/Vec3.h"

using namespace std;

class Texture {
    public:
        SDL_Color **matrizDeCores = nullptr;
        int w, h;

        Texture();
        Texture(const char* filePath);
        Texture(const char* filePath, bool isRGB);
        void initializeMatrix(int w, int h); 
        bool readFromFilePath(const char* filePath, int interval = 4);
        SDL_Color sample(Vec3 p);

        void testColors();
};