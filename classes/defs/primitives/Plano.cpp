#include "../../headers/primitives/Plano.h"
#include <math.h>

using namespace std;

Plano::Plano(int id, BaseMaterial material, Vec3 Ppi) : Objeto(id, { 0,0,0,0 }, material), Ppi(Ppi), textura(nullptr) {};

Plano::Plano(int id, SDL_Color cor, BaseMaterial material, Vec3 Ppi, Vec3 n) :
    Objeto(id, cor, material), Ppi(Ppi), n(n), textura(nullptr) {};

Plano::Plano(int id, SDL_Color cor, BaseMaterial material, Vec3 Ppi, Vec3 n, Texture* textura) :
    Objeto(id, cor, material), Ppi(Ppi), n(n), textura(textura) {};

Plano::Plano(int id, SDL_Color cor, BaseMaterial material, Vec3 Ppi) :
    Objeto(id, cor, material), Ppi(Ppi), textura(nullptr)  {};

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

    if (this->textura == nullptr)
        return LPointGetType(tint, n, Pint);

    // cout << "X E Y: " << n.x << ' ' << n.y << ' ' << n.z <<  endl;

    double uMag = sqrt(n.x*n.x + n.y*n.y);
    Vec3 uDir = Vec3(n.y/uMag, -n.y/uMag, 0);
    Vec3 vDir = n.cross(uDir);
    double uvScaling = 0.01;

    // cout << "INFO1: " << uMag << endl;
    // cout << "INFO2: " << uDir << endl;
    // cout << "INFO3: " << vDir << endl;
    // cout << "INFO4: " << uvScaling << endl;

    Vec3 uv = Vec3(uDir.dot(Pint), vDir.dot(Pint), 0)*uvScaling;
    // cout << "UV: " << endl;

    uv.y = 1 - uv.y;

	uv.x -= floor(uv.x);
	uv.y -= floor(uv.y);

    SDL_Color cor = this->textura->sample(uv);
    Vec3 novoKDifuso(
        cor.r,
        cor.g,
        cor.b
    );
    novoKDifuso = novoKDifuso.div(255);
    BaseMaterial material = BaseMaterial(novoKDifuso, this->material.REFLETIVIDADE, novoKDifuso, this->material.M);
    return LPointGetType(tint, n, Pint, material);
    
}

bool Plano::inside(Vec3 centro, double tamanho) {
    return (Ppi - centro).dot(n) < tamanho;
}

