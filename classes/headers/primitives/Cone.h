#pragma once

#include <optional>
#include "../math/Vec3.h"
#include "./ObjetoComposto.h"
#include "../Ray.h"
#include "../types/LPointGetType.h"
#include "../materiais/BaseMaterial.h"
#include "./Circulo.h"

class Cone : public Objeto {
    public:
    Vec3 Cb, Vt, d;
    double r, h;

    Circulo* base;

    Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 Vt, double r);
    Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 Vt, double r, BaseMaterial material);
    Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 direcao, double altura, double raio);
    Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 direcao, double altura, double raio, BaseMaterial material);

    std::optional<LPointGetType> intersectaFace(Ray raycaster);
    std::optional<LPointGetType> intersecta(Ray raycaster) override;
    void printObj() override;
};