#include "../../headers/materiais/BaseMaterial.h"

using namespace std;

BaseMaterial::BaseMaterial() : RUGOSIDADE(Vec3(1, 1, 1)), REFLETIVIDADE(Vec3(1, 1, 1)), KAMBIENTE(Vec3(1, 1, 1)), M(1) {}

// difusa, especular e ambiente respectivamente
BaseMaterial::BaseMaterial(Vec3 RUGOSIDADE, Vec3 REFLETIVIDADE, Vec3 KAmbiente, double M) : RUGOSIDADE(RUGOSIDADE), REFLETIVIDADE(REFLETIVIDADE), KAMBIENTE(KAmbiente), M(M) {};

BaseMaterial::BaseMaterial(Vec3 RUGOSIDADE, Vec3 REFLETIVIDADE, double M) : RUGOSIDADE(RUGOSIDADE), REFLETIVIDADE(REFLETIVIDADE), KAMBIENTE(Vec3(1, 1, 1)), M(M) {};


Vec3 BaseMaterial::getRugosidade() {
    return RUGOSIDADE;
}

Vec3 BaseMaterial::getRefletividade() {
    return REFLETIVIDADE;
}

Vec3 BaseMaterial::getKAmbiente() {
    return KAMBIENTE;
}

double BaseMaterial::getM() {
    return M;
}