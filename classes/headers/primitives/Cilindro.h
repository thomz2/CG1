#pragma once

#include <optional>
#include "../math/Vec3.h"
#include "../math/Vec4.h"
#include "../math/Transformations.h"
#include "./ObjetoComposto.h"
#include "../types/LPointGetType.h"
#include "../Ray.h"
#include "../materiais/BaseMaterial.h"
#include "./circulo.h"

class Cilindro : public Objeto {

    public:
    Vec3 Cb, Ct, d;
    double r, h;

    Circulo* circuloTopo;
    Circulo* circuloBase;
    
    Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 Ct, double r);
    Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 Ct, double r, BaseMaterial material);
    Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 direcao, double altura, double raio);
    Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 direcao, double altura, double raio, BaseMaterial material);
    
    Vec3 getW(Vec3 Pin);
    void update(Vec3 Cb, Vec3 Ct, double raio = -1);
    std::optional<LPointGetType> intersecta(Ray raycaster) override;
    std::optional<LPointGetType> intersectaFace(Ray raycaster);
    int printObj(bool printMenu = false) override;
    void handleChange(int option) override;
};