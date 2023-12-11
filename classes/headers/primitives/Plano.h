#pragma once

#include "./Objeto.h"
#include "./mesh/Texture.h"
#include "../math/Vec3.h"
#include "../types/LPointGetType.h"

class Plano : public Objeto {

public:

    Vec3 Ppi;
    Vec3 n;

    Texture* textura;

    Plano(int id, BaseMaterial material, Vec3 Ppi);
    Plano(int id, SDL_Color cor, BaseMaterial material, Vec3 Ppi, Vec3 n);
    Plano(int id, SDL_Color cor, BaseMaterial material, Vec3 Ppi, Vec3 n, Texture* textura);
    Plano(int id, SDL_Color cor, BaseMaterial material, Vec3 Ppi);

    void setNormal(Vec3 normal);
    std::optional<LPointGetType> intersecta(Ray raycaster) override;
    bool inside(Vec3 centro, double tamanho);

    int printObj(bool printMenu = false) override;
    void handleChange(int option) override;


};