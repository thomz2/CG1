#include <iostream>
// #include <SDL2/SDL.h>
#include "classes/headers/vec3.h"

using namespace std;

int main () {

    Vec3 novovetor(2, 4, -2);
    Vec3 novovetor2(1, 5, 7);  
    cout << novovetor.modulo() << endl; // OK
    cout << novovetor.norm() << endl; // OK
    cout << novovetor.prodEscalar(novovetor2) << endl; // OK
    cout << novovetor * novovetor2 << endl;
}