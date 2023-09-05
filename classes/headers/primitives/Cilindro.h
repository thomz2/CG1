#pragma once

#include <optional>
#include "../math/Vec3.h"
#include "./ObjetoComposto.h"
#include "../Ray.h"

class Cilindro : public ObjetoComposto {

    public:
    Vec3 Cb, Ct, d;
    double r, h;

    Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 Ct, double r);
    
    Vec3 getW(Vec3 Pin);
    std::optional<double> intersecta(Ray raycaster) override;
};