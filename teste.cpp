#include <iostream>
#include <SDL.h>
#include "classes/headers/math/Vec3.h"
#include "classes/headers/primitives/Esfera.h"
#include "classes/headers/primitives/Cilindro.h"
#include "classes/headers/primitives/Cone.h"
#include "classes/headers/Canvas.h"
#include "classes/headers/Ray.h"
#include "classes/headers/Scene.h"
#include "classes/headers/materiais/BaseMaterial.h"
#include "classes/headers/materiais/MaterialTarefa.h"
using namespace std;

int m10 () {

    // Vec3 novovetor(2, 4, -2);
    // Vec3 novovetor2(1, 5, 7);  
    // cout << novovetor.modulo() << endl; // OK
    // cout << novovetor.norm() << endl; // OK
    // cout << novovetor.prodEscalar(novovetor2) << endl; // OK
    // cout << novovetor * novovetor2 << endl;

    // SDL_Color cor = {100, 100, 100, 100};
    // cout << cor.r << endl;

    MaterialTarefa material = MaterialTarefa();
    cout << material.getRefletividade() << endl;

    return 0;
}