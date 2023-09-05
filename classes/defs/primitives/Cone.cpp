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

    Vec3 dr = raycaster.direcao, v = this->Vt - raycaster.Pinicial, n = this->d;
    double costheta = h / sqrt(pow(h,2) + pow(r, 2)); 
    double costhetaaoquadrado = costheta * costheta;

    double a = pow((dr.dot(v)), 2) - ((dr.dot(dr) * costhetaaoquadrado));
    double b = v.dot(dr) * costhetaaoquadrado - (v.dot(n) * dr.dot(n));
    double c = pow(v.dot(n), 2) - v.dot(v) * costhetaaoquadrado;

    double D = pow(b, 2) - 4 * a * c; // nas notas de aula ta b*b - ac 

    if (D < 0) return nullopt;

    double t1 = (-b - sqrt(D)) / (2*a); 
    double t2 = (-b + sqrt(D)) / (2*a);
}