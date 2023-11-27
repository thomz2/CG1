#pragma once
#include <SDL2/SDL.h>
#include "./Camera.h"

class Controller {
    public:
    static void handleCameraEvent(Camera* camera, SDL_Event& event);
};