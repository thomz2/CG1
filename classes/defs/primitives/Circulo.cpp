#include "../../headers/primitives/Circulo.h"

using namespace std;

Circulo::Circulo(int id, SDL_Color cor, BaseMaterial material, Vec3 centro, Vec3 n, double raio) :
    Plano(id, cor, material, centro, n), raio(raio) {};

Circulo::Circulo(int id, SDL_Color cor, BaseMaterial material, Vec3 centro, double raio) : 
    Plano(id, cor, material, centro), raio(raio) {};

Circulo::Circulo(int id, SDL_Color cor, BaseMaterial material, Vec3 centro) : 
    Plano(id, cor, material, centro) {};

void Circulo::update(Vec3 centro, Vec3 n) {
    this->Ppi = centro;
    this->n = n;
}

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

void Circulo::printObj() {
    std::cout << "Circle ID: " << id << std::endl;
    std::cout << "Center: (" << Ppi.x << ", " << Ppi.y << ", " << Ppi.z << ")" << std::endl;
    std::cout << "Normal (n): (" << n.x << ", " << n.y << ", " << n.z << ")" << std::endl;
    std::cout << "Radius: " << raio << std::endl;
}