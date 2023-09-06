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

}

optional<double> Cone::intersecta(Ray raycaster) {

    Vec3 dr = raycaster.direcao, v = this->Vt - raycaster.Pinicial, n = this->d, Po = raycaster.Pinicial;
    double cost = this->h / sqrt(pow(this->h,2) + pow(this->r,2)); 
    double costt = cost * cost;

    double a = pow(dr.dot(n), 2) - ((dr.dot(dr) * costt));
    double b = 2 * v.dot(dr) * costt - 2 * (v.dot(n) * dr.dot(n));
    double c = pow(v.dot(n), 2) - v.dot(v) * costt;

    double D = pow(b, 2) - 4 * a * c; // nas notas de aula ta b*b - ac 

    if (D <= 0) return nullopt;

    double t1 = (-b - sqrt(D)) / (2*a); 
    double t2 = (-b + sqrt(D)) / (2*a);

    Vec3 Pint1 = (dr*t1) + Po;
    Vec3 Pint2 = (dr*t2) + Po;

    // 0 <= (V - P).n <= H

    Vec3 aux1 = this->Vt - Pint1;
    Vec3 aux2 = this->Vt - Pint2;

    double dist1 = n.dot(aux1);
    double dist2 = n.dot(aux2);

    // // if (dist1 <= h && dist1 >= 0) {
    // //     if (dist2 <= h && dist2 >= 0 && t2 < t1) return t2;
    // //     else return t1;
    // // } else if (dist2 <= h && dist2 >= 0) return t2;

    if (dist1 <= h && dist1 >= 0 && dist2 <= h && dist2 >= 0) {
        return t2 < t1 ? t2 : t1; 
    } else if (dist1 <= h && dist1 >= 0) {
        return t1;
    } else if (dist2 <= h && dist2 >= 0) {
        return t2;
    } 

    return nullopt;
}