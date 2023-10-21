#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <math.h>
#include <utility>
#include "Canvas.h"
#include "primitives/Objeto.h"
#include "math/Vec3.h"
#include "Ray.h"
#include <map>
#include "luzes/Luz.h"
#include "types/LPointGetType.h"

using namespace std;

// TODO: falta especificar algumas funcoes
class Scene {

    public:
    int width, height;

    SDL_Window **window;
    SDL_Renderer **renderer;

    Canvas *canvas;

    std::vector<Objeto*> objetos;
    std::vector<Luz*>    luzes;

    Vec3 luzAmbiente;

    Scene(SDL_Window **window, SDL_Renderer **renderer, int width, int height);
    Scene(SDL_Window **window, SDL_Renderer **renderer, int width, int height, Vec3 luzAmbiente);

    private: void initializeSDLandWindow(int width, int height);

    public: 
    bool setCanvas(int nLin, int nCol, double dX, double dY);

    vector  <pair<Objeto*, LPointGetType>> intersectaObjetos(Ray raycaster); // TODO: colocar ordem de intersecção
    optional<pair<Objeto*, LPointGetType>> firstObj(Ray raycaster);

    void pintarCanvas(double dJanela, Vec3& olhoPintor);
};

