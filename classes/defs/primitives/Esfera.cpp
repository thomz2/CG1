#include <SDL2/SDL.h>
#include "../headers/primitives/Esfera.h"
#include "../headers/primitives/Objeto.h"
#include "../headers/Ray.h"
#include "../headers/math/Vec3.h"

using namespace std;

Esfera::Esfera(int id, SDL_Color cor, Vec3 PCentro, double raio) : 
    Objeto(id, cor), PCentro(PCentro), raio(raio) {

}

// Pin = olho observador
Vec3 Esfera::getW(Vec3 Pin) {
    return Pin - this->PCentro;
}

bool Esfera::intersecta(Ray raycaster) {

    Vec3 w = this->getW(raycaster.Pinicial);

    double a = raycaster.direcao.prodEscalar(raycaster.direcao);
    
    double bbarra = w.prodEscalar(raycaster.direcao);

    double b = 2 * bbarra;

    double c = w.prodEscalar(w) - this->raio*this->raio;

    double D = bbarra*bbarra - c;

    return D >= 0 ? true : false; 
}