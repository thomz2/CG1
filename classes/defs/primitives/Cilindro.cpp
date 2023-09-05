#include <SDL2/SDL.h>
#include <math.h>
#include "../../headers/primitives/Cilindro.h"
#include "../../headers/primitives/Objeto.h"
#include "../../headers/Ray.h"
#include "../../headers/math/Vec3.h"

using namespace std;

Cilindro::Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 Ct, double r) : ObjetoComposto(id, cor), Cb(Cb), Ct(Ct), r(r) {

    Vec3 dif = Ct - Cb;

    this->h = dif.modulo(); // altura = comprimento do vetor diferença
    this->d = dif.norm();   // direcao = normalizacao do vetor diferença (unitario aqui)

    // TODO: Instanciar faces nos subobjetos
};

Vec3 Cilindro::getW(Vec3 Pin) {
    return Pin - this->Cb;
}

optional<double> Cilindro::intersecta(Ray raycaster) {

    Vec3 dr = raycaster.direcao, w = this->getW(raycaster.Pinicial), dc = this->d;

    double a = dr.dot(dr) - pow((dr.dot(dc)), 2);
    double b = (2 * w.dot(dr)) - ((2 * (w.dot(dc))) * (dr.dot(dc)));
    double c = w.dot(w) - pow(w.dot(dc), 2) - (this->r * this->r);

    double D = pow(b,2) - 4 * a * c;

    if (D < 0) return nullopt;

    // TODO: checar se a distância da projeção pro ponto da base n é negativo nem maior que a altura

    double t1, t2; 
    t1 = (-b - sqrt(D)) / (2*a); t2 = (-b + sqrt(D)) / (2*a);
    Vec3 Po = raycaster.Pinicial;

    Vec3 Pint1 = (dr*t1) + Po;
    Vec3 Pint2 = (dr*t2) + Po;

    Vec3 v1 = Pint1 - Cb;
    Vec3 v2 = Pint2 - Cb;

    Vec3 proj1 = dc * (v1.dot(dc));
    Vec3 proj2 = dc * (v2.dot(dc));

    double dist1 = proj1.modulo();
    double dist2 = proj2.modulo();

    if (proj1.dot(this->d) > 0 && dist1 < this->h) { // se uma distancia existe
        // if (dist2 > 0 && dist2 < this->h && t2 < t1) return t2; // se a outra tbm existe
        if (proj2.dot(this->d) > 0 && dist2 < this->h && t2 < t1) return t2; // se a outra tbm existe
        else return t1; // se apenas a primeira existe
    } 
    // else if (dist2 > 0 && dist2 < this->h) return t2; // se apenas a segunda existe
    else if (proj2.dot(this->d) > 0 && dist2 < this->h) return t2; // se apenas a segunda existe
    
    return nullopt;
}