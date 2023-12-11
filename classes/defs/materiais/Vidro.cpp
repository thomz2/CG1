#include "../../headers/materiais/Vidro.h"

using namespace std;

Vidro::Vidro() :
    BaseMaterial(Vec3(0.1, 0.1, 0.1), Vec3(0.9, 0.9, 0.9), Vec3(0.0, 0.0, 0.0), 100) {}