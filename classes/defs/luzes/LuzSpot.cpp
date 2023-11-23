#include "../../headers/luzes/LuzSpot.h"
#include <math.h>
#define M_PI 3.14159265358979323846

using namespace std;

LuzSpot::LuzSpot(Vec3 posicao, Vec3 intensidade, Vec3 direcao, double GRAUS) 
    : LuzPontual(posicao, intensidade), direcao(direcao), theta(GRAUS * (M_PI/180)) {}

Vec3 LuzSpot::calcIntensity(vector<Objeto*> objs, LPointGetType retorno, Ray raycaster, BaseMaterial material) {
    double cosine = cos(theta);
    Vec3 lv = (this->posicao.sub(retorno.posContato)).norm();

    if (cosine <= (lv.mult(-1).dot(this->direcao)))
        return LuzPontual::calcIntensity(objs, retorno, raycaster, material);
    
    return Vec3(0, 0, 0);
}
