#include <SDL2/SDL.h>
#include <math.h>
#include "../../headers/primitives/Cilindro.h"
#include "../../headers/primitives/Objeto.h"
#include "../../headers/Ray.h"
#include "../../headers/math/Vec3.h"
#include "../../headers/primitives/Circulo.h"

using namespace std;

Cilindro::Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 Ct, double r) : ObjetoComposto(id, cor), Cb(Cb), Ct(Ct), r(r) {

    Vec3 dif = Ct - Cb;

    this->h = dif.modulo(); // altura = comprimento do vetor diferença
    this->d = dif.norm();   // direcao = normalizacao do vetor diferença (unitario aqui)

    // TODO: Instanciar faces nos subobjetos
    this->circuloTopo = new Circulo(10000 + id, cor, BaseMaterial(), Ct, dif, r);
    this->circuloBase = new Circulo(10000 + id, cor, BaseMaterial(), Cb, Cb - Ct, r);
};

Cilindro::Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 Ct, double r, BaseMaterial material) : ObjetoComposto(id, cor, material), Cb(Cb), Ct(Ct), r(r) {

    Vec3 dif = Ct - Cb;

    this->h = dif.modulo(); // altura = comprimento do vetor diferença
    this->d = dif.norm();   // direcao = normalizacao do vetor diferença (unitario aqui)

    // TODO: Instanciar faces nos subobjetos
    this->circuloTopo = new Circulo(10000 + id, cor, material, Ct, dif, r);
    this->circuloBase = new Circulo(10000 + id, cor, material, Cb, Cb - Ct, r);
};

Cilindro::Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 direcao, double altura, double raio) : ObjetoComposto(id, cor), Cb(Cb), d(direcao), h(altura), r(raio) {
    this->Ct = Cb.add(direcao.mult(altura));
    this->circuloTopo = new Circulo(10000 + id, cor, material, Ct, Ct - Cb, r);
    this->circuloBase = new Circulo(10000 + id, cor, material, Cb, Cb - Ct, r);    
}

Cilindro::Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 direcao, double altura, double raio, BaseMaterial material) : ObjetoComposto(id, cor, material), Cb(Cb), d(direcao), h(altura), r(raio) {
    this->Ct = Cb.add(direcao.mult(altura));
    this->circuloTopo = new Circulo(10000 + id, cor, material, Ct, Ct - Cb, r);
    this->circuloBase = new Circulo(10000 + id, cor, material, Cb, Cb - Ct, r);    
}

Vec3 Cilindro::getW(Vec3 Pin) {
    return Pin - this->Cb;
}

optional<LPointGetType> Cilindro::intersectaFace(Ray raycaster) {
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

    if (proj1.dot(this->d) > 0 && dist1 < this->h) { // se uma distancia existe

        if (proj2.dot(this->d) > 0 && dist2 < this->h && t2 < t1) 
            return LPointGetType(t2, hv2, Pint2); // se a outra tbm existe
        
        else return LPointGetType(t1, hv1, Pint1); // se apenas a primeira existe
    } 

    else if (proj2.dot(this->d) > 0 && dist2 < this->h) return LPointGetType(t2, hv2, Pint2); // se apenas a segunda existe

    return nullopt;
}

/*
interseccoes: 

base e face (ver qual ta mais perto)
topo e face (ver qual ta mais perto)
face somente 
base e topo (apenas ver qual ta mais perto, nao precisa calcular face)
*/ 
optional<LPointGetType> Cilindro::intersecta(Ray raycaster) {

    // checar interseccao das bases
    optional<LPointGetType> intersectCT = this->circuloTopo->intersecta(raycaster);
    optional<LPointGetType> intersectCB = this->circuloBase->intersecta(raycaster);

    // caso em que o raio intersecta as duas bases -o=o->
    if (intersectCB.has_value() && intersectCT.has_value()) {

        // circulo da base aparece primeiro?         
        // se nao aparece, o circulo do topo aparece primeiro
        return intersectCB.value().tint < intersectCT.value().tint ? intersectCB.value() : intersectCT.value();

    } else {
        
        // casos em que possivelmente a face eh intersectada
        optional<LPointGetType> intersectFace = this->intersectaFace(raycaster);
        if (!intersectFace.has_value()) return nullopt; // nao intersectou o topo e a base e nem a face, entao nao paro por aqui

        if (intersectCB.has_value()) { // caso em que intersecta base e face

            // circulo da base aparece primeiro?
            // se nao aparece, a face aparece primeiro
            return intersectCB.value().tint < intersectFace.value().tint ? intersectCB.value() : intersectFace.value();

        } else if (intersectCT.has_value()) { // caso em que intersecta topo e face

            // circulo do topo aparece primeiro?
            // se nao aparece, a face aparece primeiro
            return intersectCT.value().tint < intersectFace.value().tint ? intersectCT.value() : intersectFace.value();

        } else { // caso em que intersecta face apenas
            return intersectFace.value();
        }

    } 

    // caso nao de certo, retorna nada (nunca chega aqui)
    return nullopt;
    
}