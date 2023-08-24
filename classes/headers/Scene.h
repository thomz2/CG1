#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Canvas.h"
#include "primitives/Objeto.h"
#include "math/Vec3.h"
#include "Ray.h"

using std::vector;

class Scene {

    public:
    int width, height;

    SDL_Window **window;
    SDL_Renderer **renderer;

    Canvas *canvas;

    std::vector<Objeto*> objetos;

    Scene(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

    private: void initializeSDLandWindow(int width, int height);

    public: 
    bool setCanvas(int nLin, int nCol, double dX, double dY);

    vector<Objeto*> intersectaObjetos(Ray raycaster);

    void pintarCanvas(double dJanela, Vec3& olhoPintor);
};

