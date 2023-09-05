#include <SDL2/SDL.h>
#include <math.h>
#include "../../headers/primitives/Esfera.h"
#include "../../headers/primitives/Objeto.h"
#include "../../headers/Ray.h"
#include "../../headers/math/Vec3.h"

using namespace std;

Esfera::Esfera(int id, SDL_Color cor, Vec3 PCentro, double raio) : 
    Objeto(id, cor), PCentro(PCentro), raio(raio) {

}

// Pin = olho observador
Vec3 Esfera::getW(Vec3 Pin) {
    return Pin - this->PCentro;
}

// TODO: ajeitar isso aqui depois
optional<double> Esfera::intersecta(Ray raycaster) {

    Vec3 w = this->getW(raycaster.Pinicial);

    double a = raycaster.direcao.dot(raycaster.direcao);
    
    double bbarra = w.dot(raycaster.direcao);

    double b = 2 * bbarra;

    double c = w.dot(w) - (this->raio*this->raio);

    // double D = bbarra*bbarra - c;
    double D = pow(b, 2) - 4 * a * c;

    double t1 = (-b - sqrt(D)) / (2*a); 
    double t2 = (-b + sqrt(D)) / (2*a);

    if (D >= 0) 
        return t1 > t2 ? t2 : t1; // retorna a distancia mais perto 
    else 
        return nullopt;
}