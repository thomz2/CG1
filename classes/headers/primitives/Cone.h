#pragma once

#include <optional>
#include "../math/Vec3.h"
#include "./ObjetoComposto.h"
#include "../Ray.h"
#include "../types/LPointGetType.h"
#include "../materiais/BaseMaterial.h"

class Cone : public ObjetoComposto {
    public:
    Vec3 Cb, Vt, d;
    double r, h;

    Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 Vt, double r);
    Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 Vt, double r, BaseMaterial material);

    Vec3 getW(Vec3 Pin);
    std::optional<LPointGetType> intersecta(Ray raycaster) override;
};