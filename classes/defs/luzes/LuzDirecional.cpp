#include "../../headers/luzes/LuzDirecional.h"
#include "../../headers/Ray.h"
#include <math.h>
#include <limits.h>

using namespace std;

LuzDirecional::LuzDirecional(Vec3 intensidade, Vec3 direcao) : Luz(Vec3(0, 0, 0), intensidade), direcao(direcao) {}

Vec3 LuzDirecional::calcIntensity(vector<Objeto*> objs, LPointGetType retorno, Ray raycaster, BaseMaterial material) {

    Vec3 ponto_mais_prox = retorno.posContato;
    Vec3 normal          = retorno.normalContato.norm();
    double tint          = retorno.tint;

    LuzDirecional* luz = this;

    Vec3 lv = (Vec3(0,0,0) - luz->direcao).norm();
    Vec3 vv = Vec3(-raycaster.direcao.x, -raycaster.direcao.y, -raycaster.direcao.z);
    Vec3 rv = normal * (2 * (lv.dot(normal))) - lv;

    Ray raisombra = Ray(ponto_mais_prox, this->direcao.mult(-1));
    bool temSombra = false;
    for (auto* objeto : objs) {
        optional<LPointGetType> interseccao = objeto->intersecta(raisombra);
        if (interseccao.has_value() && interseccao.value().tint > 1) {
            // temSombra = true; break;
            return Vec3(0, 0, 0); // intensidade vazia
        }
    }

    double f_dif = max(0.0, lv.dot(normal));
    double f_esp = pow(max(0.0, vv.dot(rv)), material.getM());

    // usando operador @ (|)
    Vec3 aux1 = ((material.getRugosidade()) * f_dif);
    Vec3 aux2 = ((material.getRefletividade()) * f_esp);

    Vec3 iDif = luz->intensidade | aux1;
    Vec3 iEsp = luz->intensidade | aux2;

    return iDif.add(iEsp);
            
}
