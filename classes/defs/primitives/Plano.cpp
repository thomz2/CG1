#include "../../headers/primitives/Plano.h"

using namespace std;

Plano::Plano(int id, SDL_Color cor, BaseMaterial material, Vec3 Ppi, Vec3 n) :
    Objeto(id, cor, material), Ppi(Ppi), n(n) {};

Plano::Plano(int id, SDL_Color cor, BaseMaterial material, Vec3 Ppi) :
    Objeto(id, cor, material), Ppi(Ppi) {};

void Plano::setNormal(Vec3 normal) {
    this->n = normal;
}

std::optional<LPointGetType> Plano::intersecta(Ray raycaster) {
   
    double denom = raycaster.direcao.dot(n);
    if (denom == 0) return nullopt;

    double tint = (Ppi - raycaster.Pinicial).dot(n) / denom;
    if (tint < 0) return nullopt;

    Vec3 aux = raycaster.direcao.mult(tint);
    Vec3 Pint = raycaster.Pinicial.add(aux);

    return LPointGetType(tint, n, Pint);
}

bool Plano::inside(Vec3 centro, double tamanho) {
    return (Ppi - centro).dot(n) < tamanho;
}

