#include <SDL2/SDL.h>
#include <math.h>
#include "../../headers/primitives/Cone.h"
#include "../../headers/primitives/Objeto.h"
#include "../../headers/Ray.h"
#include "../../headers/math/Vec3.h"

using namespace std;

Cone::Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 Vt, double r) : ObjetoComposto(id, cor), Cb(Cb), Vt(Vt), r(r) {
    
    Vec3 dif = Vt - Cb;
    
    // mesma coisa do cilindro
    this->h = dif.modulo();
    this->d = dif.norm();
    
    // TODO: Instanciar faces nos subobjetos
    this->base = new Circulo(10000 + id, cor, BaseMaterial(), Cb, Cb - Vt, r);

}

Cone::Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 Vt, double r, BaseMaterial material) : ObjetoComposto(id, cor, material), Cb(Cb), Vt(Vt), r(r) {
    
    Vec3 dif = Vt - Cb;
    
    // mesma coisa do cilindro
    this->h = dif.modulo();
    this->d = dif.norm();
    
    // TODO: Instanciar faces nos subobjetos
    this->base = new Circulo(10000 + id, cor, material, Cb, Cb - Vt, r);
}

optional<LPointGetType> Cone::intersectaFace(Ray raycaster) {

    Vec3 dr = raycaster.direcao, v = this->Vt - raycaster.Pinicial, n = this->d, Po = raycaster.Pinicial;
    Vec3 vv = Vec3(-dr.x, -dr.y, -dr.z);

    double cost = this->h / sqrt(pow(this->h,2) + pow(this->r,2)); 
    double costt = cost * cost;

    double a = pow(dr.dot(n), 2) - ((dr.dot(dr) * costt));
    double b = 2 * v.dot(dr) * costt - 2 * (v.dot(n) * dr.dot(n));
    double c = pow(v.dot(n), 2) - v.dot(v) * costt;

    double D = pow(b, 2) - 4 * a * c; // nas notas de aula ta b*b - ac 

    if (D <= 0) return nullopt;

    double t1 = (-b - sqrt(D)) / (2*a); 
    double t2 = (-b + sqrt(D)) / (2*a);
    
    // condição do a = 0, ver melhor depois
    if (a == 0) {
        t1 = t2 = (-c) / (2*b);
    }

    Vec3 Pint1 = (dr*t1) + Po;
    Vec3 Pint2 = (dr*t2) + Po;

    // 0 <= (V - P).n <= H

    Vec3 aux1 = this->Vt - Pint1;
    Vec3 aux2 = this->Vt - Pint2;

    double dist1 = n.dot(aux1);
    double dist2 = n.dot(aux2);

    // ((Pint->v x dc) x (Pint->V)).norm()
    // TODO: TA COM ERRO AQUI EMBAIXO :D

    Vec3 qseNormal1 = (aux1 * d) * aux1;
    Vec3 qseNormal2 = (aux2 * d) * aux2;

    if (dist1 <= h && dist1 >= 0 && dist2 <= h && dist2 >= 0) {
        // return t2 < t1 ? t2 : t1; 
        return t2 < t1 ? 
            LPointGetType(t2, qseNormal2.norm(), Pint2) : 
            LPointGetType(t1, qseNormal1.norm(), Pint1); 
    } else if (dist1 <= h && dist1 >= 0) {
        // return t1;
        return LPointGetType(t1, qseNormal1.norm(), Pint1); 
    } else if (dist2 <= h && dist2 >= 0) {
        // return t2;
        return LPointGetType(t2, qseNormal1.norm(), Pint2); 
    } 

    return nullopt;
}

optional<LPointGetType> Cone::intersecta(Ray raycaster) {

    optional<LPointGetType> intersectCB = this->base->intersecta(raycaster);
    optional<LPointGetType> intersectFace = this->intersectaFace(raycaster);
    
    // se nao passou por nenhum retorna logo
    if (!intersectCB.has_value() && !intersectFace.has_value()) 
        return nullopt; 
    
    if (intersectFace.has_value() && !intersectCB.has_value()) {
        return intersectFace;
    } else if (intersectFace.has_value() && intersectCB.has_value()) {
        return intersectFace.value().tint < intersectCB.value().tint ? intersectFace : intersectCB;
    } else if (!intersectFace.has_value() && intersectCB.has_value()) {
        return intersectCB;
    }
    
}