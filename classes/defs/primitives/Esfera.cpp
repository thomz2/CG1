#include <SDL2/SDL.h>
#include <math.h>
#include "../../headers/primitives/Esfera.h"
#include "../../headers/primitives/Objeto.h"
#include "../../headers/Ray.h"
#include "../../headers/math/Vec3.h"
#include "../../headers/materiais/BaseMaterial.h"

using namespace std;

Esfera::Esfera(int id, SDL_Color cor, Vec3 PCentro, double raio, BaseMaterial material) : 
    Objeto(id, cor, material), PCentro(PCentro), raio(raio) {}

Esfera::Esfera(int id, SDL_Color cor, Vec3 PCentro, double raio) : 
    Objeto(id, cor), PCentro(PCentro), raio(raio) {}

// Pin = olho observador
Vec3 Esfera::getW(Vec3 Pin) {
    return Pin - this->PCentro;
}

// TODO: ajeitar isso aqui depois
optional<LPointGetType> Esfera::intersecta(Ray raycaster) {

    Vec3 w = this->getW(raycaster.Pinicial);

    double a = raycaster.direcao.dot(raycaster.direcao);
    
    double bbarra = w.dot(raycaster.direcao);

    double b = 2 * bbarra;

    double c = w.dot(w) - (this->raio*this->raio);

    // double D = bbarra*bbarra - c;
    double D = pow(b, 2) - 4 * a * c;

    double t1 = (-b - sqrt(D)) / (2*a); 
    double t2 = (-b + sqrt(D)) / (2*a);

    double tint;

    if (D >= 0) {
        tint = (t1 > t2 ? t2 : t1); // distancia mais perto 
        if (t1 < 0 && t2 >= 0) tint = t2;
        if (t2 < 0 && t1 >= 0) tint = t1;
        if (tint < 0) return nullopt;
    } 
    else 
        return nullopt;

    Vec3 direcaodottint = raycaster.direcao * tint; 
    Vec3 Pint           = direcaodottint + raycaster.Pinicial;
    Vec3 normContato    = (Pint - PCentro).norm();

                      // tint, normalcontato, poscontato
    return LPointGetType(tint, normContato, Pint);

}

void Esfera::printObj() {
    std::cout << "Sphere ID: " << id << std::endl;
    std::cout << "Center (PCentro): (" << PCentro.x << ", " << PCentro.y << ", " << PCentro.z << ")" << std::endl;
    std::cout << "Radius (raio): " << raio << std::endl;

    material.printMaterial();

    cout << "Deseja fazer algo?" << endl;
    cout << "[0] não" << endl;
    cout << "[1] transladar" << endl;
    cout << "[2] aumentar raio" << endl;
    cout << "[3] mudar material" << endl;
    int opcao = 0;
    cin >> opcao;
    if (opcao == 0) return; 
}