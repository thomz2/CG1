#pragma once

#include <optional>
#include <SDL2/SDL.h>
#include <optional>
#include "../Ray.h"
#include "../types/LPointGetType.h"
#include "../materiais/BaseMaterial.h"

class Objeto {

public:

    int id;
    std::optional<SDL_Color> cor;
    BaseMaterial material;

    Objeto(int id, SDL_Color cor, BaseMaterial material);

    Objeto(int id, SDL_Color cor);

    Objeto(int id);

    virtual std::optional<LPointGetType> intersecta(Ray raycaster) = 0;
    // virtual Vec3 getNormalByPoint(Ray raycaster) = 0;
};

