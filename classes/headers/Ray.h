#pragma once

#include "./math/Vec3.h"

class Ray {
    public:
    Vec3 Pinicial, direcao;

    Ray(Vec3 Pinicial, Vec3 direcao);

};