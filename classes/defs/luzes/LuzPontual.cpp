#include "../../headers/luzes/LuzPontual.h"
#include "../../headers/Ray.h"
#include <math.h>

using namespace std;

LuzPontual::LuzPontual(Vec3 posicao, Vec3 intensidade) : Luz(posicao, intensidade) {}

Vec3 LuzPontual::calcIntensity(vector<Objeto*> objs, LPointGetType retorno, Ray raycaster, BaseMaterial material) {

    Vec3 ponto_mais_prox = retorno.posContato;
    Vec3 normal          = retorno.normalContato.norm();
    double tint          = retorno.tint;

    LuzPontual* luz = this;

    Vec3 lv = (luz->posicao - ponto_mais_prox).norm();
    Vec3 vv = Vec3(-raycaster.direcao.x, -raycaster.direcao.y, -raycaster.direcao.z);
    Vec3 rv = normal * (2 * (lv.dot(normal))) - lv;

    Ray raisombra = Ray(luz->posicao, lv * (-1));
    double L = (luz->posicao - ponto_mais_prox).modulo();
    bool temSombra = false;
    for (auto* objeto : objs) {
        optional<LPointGetType> interseccao = objeto->intersecta(raisombra);
        if (interseccao.has_value() && interseccao.value().tint < L - 0.000001) {
            // temSombra = true; break;
            return Vec3(0, 0, 0); // intensidade vazia
        }
    }

    double f_dif = max(0.0, lv.dot(normal));
    double f_esp = pow(max(0.0, vv.dot(rv)), material.getM());

    // usando operador @ (|)
    Vec3 aux1 = ((material.getRugosidade()) * f_dif);
    Vec3 aux2 = ((material.getRefletividade()) * f_esp);


    // fator de distancia
    // double distanceDecayFactor = 1 / ((luz->posicao - raycast->contact_position)).magSquared();
    // fim fator distancia

    Vec3 iDif = luz->intensidade | aux1;
    Vec3 iEsp = luz->intensidade | aux2;

    return iDif.add(iEsp);
            
}
