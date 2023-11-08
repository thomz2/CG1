#include "../../headers/materiais/MaterialTarefa.h"

using namespace std;

MaterialTarefa::MaterialTarefa() :
    BaseMaterial(Vec3(0.7, 0.2, 0.2), Vec3(0.7, 0.2, 0.2), Vec3(0.7, 0.2, 0.2), 10) {
        // this->RUGOSIDADE = Vec3(0.7, 0.2, 0.2);
        // this->REFLETIVIDADE = Vec3(0.7, 0.2, 0.2);
        // this->KAMBIENTE = Vec3(0.7, 0.2, 0.2);
        // this->M = 10;
    }