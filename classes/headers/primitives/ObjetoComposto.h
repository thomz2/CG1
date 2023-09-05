#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "../Ray.h"
#include "./Objeto.h"

class ObjetoComposto : public Objeto {

public:

    std::vector<Objeto*> subObjetos;

    ObjetoComposto(int id);
    ObjetoComposto(int id, SDL_Color cor);
};