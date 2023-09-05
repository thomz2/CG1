#pragma once

#include <optional>
#include "../math/Vec3.h"
#include "./ObjetoComposto.h"
#include "../Ray.h"

class Cone : public ObjetoComposto {
    public:
    Vec3 Cb, Vt, d;
    double r, h;

    Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 Vt, double r);

    Vec3 getW(Vec3 Pin);
    std::optional<double> intersecta(Ray raycaster) override;
};