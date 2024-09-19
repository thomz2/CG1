#include <iostream>
#include <SDL2/SDL.h>
#include <thread>
#include <vector>
#include <utility>
#include "classes/headers/math/Vec3.h"
#include "classes/headers/primitives/Esfera.h"
#include "classes/headers/primitives/EsferaDeLuzSpot.h"
#include "classes/headers/primitives/Cilindro.h"
#include "classes/headers/primitives/Cone.h"
#include "classes/headers/primitives/Arvore.h"
#include "classes/headers/Canvas.h"
#include "classes/headers/Ray.h"
#include "classes/headers/Scene.h"
#include "classes/headers/materiais/BaseMaterial.h"
#include "classes/headers/materiais/Difuso.h"
#include "classes/headers/materiais/Madeira.h"
#include "classes/headers/materiais/Pele.h"
#include "classes/headers/materiais/Metalico.h"
#include "classes/headers/materiais/Plastico.h"
#include "classes/headers/materiais/MaterialTarefa.h"
#include "classes/headers/math/Transformations.h"
#include "classes/headers/math/Mat4.h"
#include "classes/headers/math/Vec4.h"
#include "classes/headers/Camera.h"
#include "classes/headers/primitives/Triangulo.h"
#include "classes/headers/primitives/Mesh.h"
#include "classes/headers/primitives/ObjMesh.h"
#include "classes/headers/primitives/mesh/Texture.h"
#include "classes/headers/luzes/LuzPontual.h"
#include "classes/headers/luzes/LuzSpot.h"
#include "classes/headers/luzes/LuzDirecional.h"
#include "classes/headers/primitives/Cluster.h"

#include "classes/miniball/Seb.h"
using namespace std;

int main (int argc, char *argv[]) {

    // Vec3 novovetor(2, 4, -2);
    // Vec3 novovetor2(1, 5, 7);  
    // cout << novovetor.modulo() << endl; // OK
    // cout << novovetor.norm() << endl; // OK
    // cout << novovetor.prodEscalar(novovetor2) << endl; // OK
    // cout << novovetor * novovetor2 << endl;

    // SDL_Color cor = {100, 100, 100, 100};
    // cout << cor.r << endl;

    // MaterialTarefa material = MaterialTarefa();
    // cout << material.getRefletividade() << endl;

    Vec3 vet(0, 1, 0);
    cout << vet.ortogonal() << endl;

    return 0;
}