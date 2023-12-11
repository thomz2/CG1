#include "../../headers/materiais/Difuso.h"

using namespace std;

Difuso::Difuso() :
    BaseMaterial(Vec3(0.8, 0.8, 0.8), Vec3(0.2, 0.2, 0.2), Vec3(0.0, 0.0, 0.0), 10) {}