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
        void initializeMatrix(int w, int h); 
        bool readFromFilePath(const char* filePath);
        SDL_Color sample(Vec3 p);

        void testColors();
};