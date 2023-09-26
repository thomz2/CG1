#include "../headers/Scene.h"
#include <iostream>
#include <set>
#include <limits.h>
#include <utility>
#include <map>
#include <math.h>

using namespace std;

Scene::Scene(SDL_Window **window, SDL_Renderer **renderer, int width, int height) :
    window(window), renderer(renderer), width(width), height(height) {
    this->initializeSDLandWindow(width, height);
    this->canvas = nullptr;
    this->objetos = {};
    this->luzes = {};
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
/*
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
*/

// REFATORAR CODIGO RUIM
// PEGAR O OBJETO MAIS PERTO
optional<pair<Objeto*, LPointGetType>> Scene::firstObj(Ray raycaster) {

    Objeto* menordistObj = nullptr;
    double menordist = INT_FAST32_MAX;

    LPointGetType* infos = new LPointGetType();

    for (auto *obj : this->objetos) {
        auto intersecao = obj->intersecta(raycaster);
        
        if (intersecao.has_value()) {
            double datual = intersecao.value().tint;
            if (datual < menordist) {
                menordist = datual;
                menordistObj = obj;
                
                // infos adicionais
                infos->tint = intersecao.value().tint;
                infos->normalContato = intersecao.value().normalContato;
                infos->posContato = intersecao.value().posContato;
            }
        }
    }

    //TODO: DESTRUIR 'infos'

    if (menordistObj == nullptr) return nullopt;
    
    return  make_pair(menordistObj, 
        //            tint, normalcontato, posicaocontato
        LPointGetType(infos->tint, infos->normalContato, infos->posContato));
}

//TODO: FALTA SO FAZER OS CALCULOS AQUI
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

            optional<pair<Objeto*, LPointGetType>> par = this->firstObj(raycaster);
            
            // PAREI AQUI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            Objeto* maisPerto = nullptr;
            if (par.has_value()){
                maisPerto = par.value().first;
                LPointGetType retorno = par.value().second;

                Vec3 corNova(
                    maisPerto->cor.value().r,
                    maisPerto->cor.value().g,
                    maisPerto->cor.value().b
                );

                // foi intersectado
                if (maisPerto != nullptr) {

                    Vec3 ponto_mais_prox = retorno.posContato;
                    Vec3 normal          = retorno.normalContato.norm();
                    double tint          = retorno.tint;

                    Vec3 intensidadeCor = Vec3(0.2, 0.2, 0.2); // luz ambiente

                    // fazer loop da luz
                    for (Luz* luz : luzes) {
                        Vec3 lv = (luz->posicao - ponto_mais_prox).norm();
                        Vec3 vv = Vec3(-raycaster.direcao.x, -raycaster.direcao.y, -raycaster.direcao.z);
                        Vec3 rv = normal * (2 * (lv.dot(normal))) - lv;

                        double f_dif = max(0.0, lv.dot(normal));
                        // double f_esp = pow(vv.dot(rv), maisPerto->material);
                        double f_esp = pow(max(0.0, vv.dot(rv)), maisPerto->material.getM());

                        // if (f_dif < 0) f_dif = 0;
                        // if (f_esp < 0) f_esp = 0;

                        // usando operador @ (|)
                        Vec3 aux1 = ((maisPerto->material.getRugosidade()) * f_dif);
                        Vec3 aux2 = ((maisPerto->material.getRefletividade()) * f_esp);

                        Vec3 iDif = luz->intensidade | aux1;
                        Vec3 iEsp = luz->intensidade | aux2;
                    
                        // TODO: implementar intensidade ambiente
                        // Vec3 intesidade = this->ambient + iDif + iEsp;
                        Vec3 anterior = intensidadeCor;
                        intensidadeCor = anterior + iDif + iEsp;

                        if (intensidadeCor.x > 1) intensidadeCor.x = 1;
                        if (intensidadeCor.y > 1) intensidadeCor.y = 1;
                        if (intensidadeCor.z > 1) intensidadeCor.z = 1;

                        // OPERADOR @
                        corNova = corNova | intensidadeCor;

                        SDL_Color corNovaPintar = {
                            corNova.x,
                            corNova.y,
                            corNova.z,
                            255 // ver isso dps
                        };

                        this->canvas->pintarCanvas(l, c, corNovaPintar);

                    }


                    
                    // DEBUG
                    if (l == (int)(this->canvas->nLin / 2) &&  c == (int)(this->canvas->nCol / 2)) {
                        // pair<vector<Objeto*>, map<int, double>> meudebug = this->intersectaObjetos(raycaster);
                        optional<pair<Objeto*, LPointGetType>> meudebug = this->firstObj(raycaster);
                        Objeto* objeto_intersec = meudebug.value().first;
                        // map<int, double> distancias = meudebug.second;

                        // for (auto* obj : objetos_intersecs) {
                            // this->canvas->pintarCanvas(l, c, obj->cor);d
                        cout << objeto_intersec->id << ": " << meudebug.value().second.tint << endl;
                        // }
                    }
                }
            }
        }
    } 
}