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

optional<LPointGetType> Cilindro::intersecta(Ray raycaster) {

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

    Vec3 hv1 = v1 - proj1; // vetor h != unidade h
    Vec3 hv2 = v2 - proj2; // vetor h != unidade h

    double dist1 = proj1.modulo();
    double dist2 = proj2.modulo();

    // Vec3 aux1 = Pint1 - this->Cb;
    // Vec3 aux2 = Pint2 - this->Cb;

    // double distaux1 = dc.dot(aux1);
    // double distaux2 = dc.dot(aux2);

    if (proj1.dot(this->d) > 0 && dist1 < this->h) { // se uma distancia existe
        // if (dist2 > 0 && dist2 < this->h && t2 < t1) return t2; // se a outra tbm existe
        // if (proj2.dot(this->d) > 0 && dist2 < this->h && t2 < t1) return t2; // se a outra tbm existe
        if (proj2.dot(this->d) > 0 && dist2 < this->h && t2 < t1) return LPointGetType(t2, hv2, Pint2); // se a outra tbm existe
        
        // else return t1; // se apenas a primeira existe
        else return LPointGetType(t1, hv1, Pint1); // se apenas a primeira existe
    } 
    // else if (dist2 > 0 && dist2 < this->h) return t2; // se apenas a segunda existe
    // else if (proj2.dot(this->d) > 0 && dist2 < this->h) return t2; // se apenas a segunda existe
    else if (proj2.dot(this->d) > 0 && dist2 < this->h) return LPointGetType(t2, hv2, Pint2); // se apenas a segunda existe
    
    // if (distaux1 <= h && distaux1 >= 0 && distaux2 <= h && distaux2 >= 0) {
    //     return t2 < t1 ? t2 : t1; 
    // } else if (distaux1 <= h && distaux1 >= 0) {
    //     return t1;
    // } else if (distaux2 <= h && distaux2 >= 0) {
    //     return t2;
    // } 

    return nullopt;
}