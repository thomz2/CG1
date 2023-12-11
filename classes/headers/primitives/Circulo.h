#pragma once

#include "./Plano.h"

class Circulo : public Plano {

public:

    double raio;

    Circulo(int id, SDL_Color cor, BaseMaterial material, Vec3 centro, Vec3 n, double raio);
    Circulo(int id, SDL_Color cor, BaseMaterial material, Vec3 centro, double raio);
    Circulo(int id, SDL_Color cor, BaseMaterial material, Vec3 centro);

    void setRaio(double raio);
    void update(Vec3 centro, Vec3 n);
    std::optional<LPointGetType> intersecta(Ray raycaster) override;
    // bool inside(Vec3 centro, double tamanho);
    
    int printObj() override;
    void handleChange(int option) override;

};