#include <SDL2/SDL.h>
#include <vector>
#include "../headers/Scene.h"
#include "../headers/Canvas.h"
#include "../headers/primitives/Objeto.h"
#include "../headers/Ray.h"

using namespace std;

Scene::Scene(SDL_Window *window, SDL_Renderer *renderer, int width, int height) :
    window(window), renderer(renderer), width(width), height(height) {
    this->initializeSDLandWindow(width, height);
    this->canvas = nullptr;
    this->objetos = {};
}

void Scene::initializeSDLandWindow(int width, int height) {
    SDL_Init (SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer (
        width, height, 0, &(this->window), &(this->renderer)
    );
    // SDL_RenderSetScale(renderer, 4, 4);
}

bool Scene::setCanvas(int nLin, int nCol, double dX, double dY) {
    this->canvas = new Canvas(nLin, nCol, dX, dY);
    if (this->canvas == nullptr) return false;

    return true;
}

vector<Objeto*> Scene::intersectaObjetos(Ray raycaster) {
    vector <Objeto*> intersectados;

    for (auto *obj : this->objetos) {
        if (obj->intersecta(raycaster)) {
            
        }
    }

    return intersectados; 
}