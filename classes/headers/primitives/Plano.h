#pragma once

#include "./Objeto.h"
#include "../math/Vec3.h"

class Plano : public Objeto {

public:

    Vec3 Ppi;
    Vec3 n;

    Plano(int id, SDL_Color cor, BaseMaterial material);


};