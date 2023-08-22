#include "../headers/Esfera.h"
#include "../headers/Ray.h"

using namespace std;

Esfera::Esfera(Vec3 PCentro, double raio) : PCentro(PCentro), raio(raio) {}

// Pin = olho observador
Vec3 Esfera::getW(Vec3 Pin) {
    return Pin - this->PCentro;
}

bool Esfera::intersecta(Ray raycaster) {

    double a = raycaster.direcao.prodEscalar(raycaster.direcao);
    
    double bbarra = this->getW(raycaster.Pinicial).prodEscalar(raycaster.direcao);

    double b = 2 * bbarra;

    double c = this->getW(raycaster.Pinicial).prodEscalar(raycaster.Pinicial) - this->raio*this->raio;

    double D = bbarra*bbarra - c;

    return D >= 0 ? true : false; 
}