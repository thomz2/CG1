#pragma once

#include <optional>
#include <SDL2/SDL.h>
#include <optional>
#include "../Ray.h"

class Objeto {

public:

    int id;
    std::optional<SDL_Color> cor;

    Objeto(int id, SDL_Color cor);

    Objeto(int id);

    virtual std::optional<double> intersecta(Ray raycaster) = 0;
};

