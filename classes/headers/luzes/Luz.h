#include "../math/Vec3.h"
#pragma once

class Luz {

public:
    Vec3 posicao;
    Vec3 intensidade;

    Luz(Vec3 posicao, Vec3 intensidade);
};