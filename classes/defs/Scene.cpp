#include "../headers/Scene.h"
#include <iostream>
#include <set>

using namespace std;

Scene::Scene(SDL_Window **window, SDL_Renderer **renderer, int width, int height) :
    window(window), renderer(renderer), width(width), height(height) {
    this->initializeSDLandWindow(width, height);
    this->canvas = nullptr;
    this->objetos = {};
}

void Scene::initializeSDLandWindow(int width, int height) {
    SDL_Init (SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer (
        width, height, 0, (this->window), (this->renderer)
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
    set <int> id_intersectados;

    for (auto *obj : this->objetos) {
        if (obj->intersecta(raycaster) && id_intersectados.count(obj->id) == 0) {
            intersectados.push_back(obj);
            id_intersectados.insert(obj->id);

            // cout << "Objeto de id " << obj->id << " adicionado!\n";
        }
    }

    return intersectados; 
}

void Scene::pintarCanvas(double dJanela, Vec3& olhoPintor) {

    const int hJanela = this->canvas->dY * this->canvas->nLin; 
    const int wJanela = this->canvas->dX * this->canvas->nCol;

    const int Dy = this->canvas->dY;
    const int Dx = this->canvas->dX;

    cout << "CANVAS: h,w: [ " << hJanela << " " << wJanela << " ] Dy, Dx: [ " << Dy << " " << Dx << " ]\n";  
    cout << "LOOP: " << this->canvas->nLin << " por " << this->canvas->nCol << endl;

    for (int l = 0; l < this->canvas->nLin; l++) {

        double y = hJanela/2 - Dy/2 - l*Dy;

        for (int c = 0; c < this->canvas->nCol; c++) {

            double x = -wJanela/2 + Dx/2 + c*Dx;

            Vec3 PosJanela(x, y, -dJanela);
            Vec3 direcao = (PosJanela - olhoPintor).norm();
            Ray raycaster(olhoPintor, direcao);

            vector<Objeto*> objetos_intersecs = this->intersectaObjetos(raycaster); 

            // if (objetos_intersecs.size() != 0) {
            //     cout << "[" << l << "]" << "[" << c << "]: "; 
            //     cout << "TAMANHO objetos intersectados: " << objetos_intersecs.size() << endl; 
            // }

            // if (objetos_intersecs.size() != 0)
            //     std::cout << objetos_intersecs[0]->cor.r << std::endl;

            for (auto* obj : objetos_intersecs) {
                this->canvas->pintarCanvas(l, c, obj->cor);
                // cout << "PINTANDO COR: " << obj->cor.r << endl;
            }

        }
    } 
}