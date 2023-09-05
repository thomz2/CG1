#include "../headers/Scene.h"
#include <iostream>
#include <set>
#include <limits.h>
#include <utility>
#include <map>

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

// ORDEM DE COLOCADA NO CENARIO
pair<vector<Objeto*>, map<int, double>> Scene::intersectaObjetos(Ray raycaster) {
    vector <Objeto*> intersectados;
    map<int, double> id_dist_intersectados; // id e distancia
    
    for (auto *obj : this->objetos) {
        if (obj->intersecta(raycaster).has_value() && id_dist_intersectados.count(obj->id) == 0) {
            intersectados.push_back(obj);
            id_dist_intersectados[obj->id] = obj->intersecta(raycaster).value();

            // cout << "Objeto de id " << obj->id << " adicionado!\n";
        }
    }

    return { intersectados, id_dist_intersectados }; 
}

// PEGAR O OBJETO MAIS PERTO
Objeto* Scene::firstObj(Ray raycaster) {

    Objeto* menordistObj = nullptr;
    double menordist = INT_FAST32_MAX;

    for (auto *obj : this->objetos) {
        auto intersecao = obj->intersecta(raycaster);
        
        if (intersecao.has_value()) {
            double datual = intersecao.value();
            if (datual < menordist) {
                menordist = datual;
                menordistObj = obj;
            }
        }
    }

    return menordistObj;
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
            Vec3 direcao = (PosJanela - olhoPintor).norm(); // vetor unitario aki
            Ray raycaster(olhoPintor, direcao);

            // vector<Objeto*> objetos_intersecs = (this->intersectaObjetos(raycaster)).first; 

            // for (auto* obj : objetos_intersecs) {
            //     this->canvas->pintarCanvas(l, c, obj->cor);
            // }

            Objeto* maisPerto = this->firstObj(raycaster);
            if (maisPerto != nullptr) {
                this->canvas->pintarCanvas(l, c, maisPerto->cor);
                
                // DEBUG
                if (l == (int)(this->canvas->nLin / 2) &&  c == (int)(this->canvas->nCol / 2)) {
                    pair<vector<Objeto*>, map<int, double>> meudebug = this->intersectaObjetos(raycaster);
                    vector<Objeto*> objetos_intersecs = meudebug.first;
                    map<int, double> distancias = meudebug.second;

                    for (auto* obj : objetos_intersecs) {
                        // this->canvas->pintarCanvas(l, c, obj->cor);d
                        cout << obj->id << ": " << distancias[obj->id] << endl;
                    }
                }
            }

        }
    } 
}