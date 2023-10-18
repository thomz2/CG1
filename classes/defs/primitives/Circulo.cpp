#include "../../headers/primitives/Circulo.h"

using namespace std;

Circulo::Circulo(int id, SDL_Color cor, BaseMaterial material, Vec3 centro, Vec3 n, double raio) :
    Plano(id, cor, material, centro, n), raio(raio) {};

Circulo::Circulo(int id, SDL_Color cor, BaseMaterial material, Vec3 centro, double raio) : 
    Plano(id, cor, material, centro), raio(raio) {};

Circulo::Circulo(int id, SDL_Color cor, BaseMaterial material, Vec3 centro) : 
    Plano(id, cor, material, centro) {};


void Circulo::setRaio(double raio) {
    this->raio = raio;
};

optional<LPointGetType> Circulo::intersecta(Ray raycaster) {

    optional<LPointGetType> ponto = this->Plano::intersecta(raycaster);
    if (ponto.has_value()) {
        if (Ppi.sub(ponto.value().posContato).modulo() > raio) {
            return nullopt;
        } 
    }

    return ponto;

};