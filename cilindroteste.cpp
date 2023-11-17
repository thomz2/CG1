// TODO: implementar destrutores nas classes

#include <iostream>
#include <SDL2/SDL.h>
#include <thread>
#include "classes/headers/math/Vec3.h"
#include "classes/headers/primitives/Esfera.h"
#include "classes/headers/primitives/Cilindro.h"
#include "classes/headers/primitives/Cone.h"
#include "classes/headers/Canvas.h"
#include "classes/headers/Ray.h"
#include "classes/headers/Scene.h"
#include "classes/headers/materiais/BaseMaterial.h"
#include "classes/headers/materiais/MaterialTarefa.h"
#include "classes/headers/math/Transformations.h"
#include "classes/headers/math/Mat4.h"
#include "classes/headers/math/Vec4.h"
#include "classes/headers/Camera.h"
#include "classes/headers/primitives/Triangulo.h"
#include "classes/headers/primitives/Mesh.h"

using namespace std;

const int WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;

void renderizarCenario(Scene* cenario, double dJanela, Vec3 olhoPintor) {
    cenario->pintarCanvas2(dJanela, olhoPintor);
}

void colorirCenario(SDL_Renderer* renderer, Scene* cenario, int nLin, int nCol) {
    for (int l = 0; l < nLin; ++l) {
        for (int c = 0; c < nCol; ++c) {
            SDL_Color cor = cenario->canvas->cores[l][c];

            SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
            SDL_RenderDrawPoint(renderer, c, l); // x = coluna que ta e y = linha que ta
        }
    }
}

int main ( int argc, char *argv[] ) {

    MaterialTarefa material = MaterialTarefa();
    cout << material.getRefletividade() << endl;


    SDL_Window *window; // = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wJanela, hJanela, SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_Renderer *renderer;


    // initializeSDLAndWindow(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    const double dJanela = 30;
    const double rEsfera = 40;
    const double zCentroEsfera = - (dJanela + rEsfera) - 50; // sempre diminuindo um valor

    Vec3 centroJanela(0, 0, -dJanela);
    Vec3 olhoPintor(-30, 0, 0);

    Camera *camera = new Camera(olhoPintor, centroJanela, Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT, Vec3(0.3, 0.3, 0.3), camera);
    const double wJanela = camera->wJanela, hJanela = camera->hJanela;

    SDL_Color corVermelha = {255, 0, 0, 255};
    SDL_Color corVerde = {0, 255, 0, 255};
    SDL_Color corAzul = {0, 0, 255, 255};

    Esfera* esfera = new Esfera(0, corVermelha, Vec3(0, 0, -100), rEsfera, MaterialTarefa());
    Plano* chao = new Plano(5, corAzul, BaseMaterial(Vec3(0.2, 0.7, 0.2), Vec3(0, 0, 0), Vec3(0.2, 0.7, 0.2), 1), Vec3(0, -55, 0), Vec3(0, 1, 0));
    Plano* planoDeFundo = new Plano(6, corVerde, BaseMaterial(Vec3(0.3, 0.3, 0.7), Vec3(0, 0, 0), Vec3(0.3, 0.3, 0.7), 1), Vec3(0, 0, -200), Vec3(0, 0, 1));
    
    Cilindro* cilindro = new Cilindro(1, corVerde, Vec3(0, 0, -100), Vec3(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3)), 3 * rEsfera, rEsfera/3, BaseMaterial(Vec3(0.2, 0.3, 0.8), Vec3(0.2, 0.3, 0.8), Vec3(0.2, 0.3, 0.8), 10));
    Cone* cone = new Cone(1, corAzul, cilindro->Ct, Vec3(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3)), 1.5 * rEsfera / 3, (1.5)*rEsfera, BaseMaterial(Vec3(0.8, 0.3, 0.2), Vec3(0.8, 0.3, 0.2), Vec3(0.8, 0.3, 0.2), 10));
    Cone* cone2 = new Cone(3, corVermelha, Vec3(200, 0, zCentroEsfera), Vec3(490, 0, zCentroEsfera - 1), 250);
    Cone* cone3 = new Cone(4, corAzul, Vec3(480, 0, zCentroEsfera), Vec3(730, 0, zCentroEsfera - 1), 250);

    Cilindro* cilindro2 = new Cilindro(10, corVermelha, Vec3(0, -30, -100), Vec3(0, 30, -100), 25, MaterialTarefa());

    Triangulo* triangulo = new Triangulo(11, BaseMaterial(), Vec3(-30, 0, -dJanela), Vec3(30,0,-dJanela), Vec3(0,30,-dJanela));

    Mesh* mesh = new Mesh(1);
    mesh->vertices.push_back(Vec3(0, 0, -dJanela));
    mesh->vertices.push_back(Vec3(30, 0, -dJanela));
    mesh->vertices.push_back(Vec3(30, 30, -dJanela));
    mesh->faces.push_back({ 0,1,2 });
    mesh->vertices.push_back({ 0,30,-dJanela });
    mesh->faces.push_back({ 0,2,3 });
    mesh->renderizar();

    Luz* luzPontual = new Luz(Vec3(0, 60, -30), Vec3(0.7, 0.7, 0.7));

    const int nCol = 500;
    const int nLin = 500;

    const double Dx = (double)wJanela / (double)nCol;
    const double Dy = (double)hJanela / (double)nLin;

    cenario->objetos.push_back(cilindro2);

    cenario->objetos.push_back(esfera);
    cenario->objetos.push_back(chao);
    cenario->objetos.push_back(planoDeFundo);
    cenario->objetos.push_back(cilindro);
    cenario->objetos.push_back(cone);
    cenario->objetos.push_back(cone2);
    cenario->objetos.push_back(cone3);
    cenario->objetos.push_back(triangulo);
    cenario->objetos.push_back(mesh);

    cenario->luzes.push_back(luzPontual);

    cenario->setCanvas(nLin, nCol, Dx, Dy);

    bool rodando = true;
    while (rodando) {

        /* 
        Vec4 Cbnovo = Vec3(cilindro2->Cb);
        Vec4 Ctnovo = Vec3(cilindro2->Ct);

        Cbnovo = Cbnovo.apply(Transformations::rotateZAroundPointDegrees(1, Vec3(0, 0, -90)).apply(Transformations::rotateXAroundPointDegrees(1, Vec3(0, 0, -90))));
        Ctnovo = Ctnovo.apply(Transformations::rotateZAroundPointDegrees(1, Vec3(0, 0, -90)).apply(Transformations::rotateXAroundPointDegrees(1, Vec3(0, 0, -90))));

        // Cbnovo = Cbnovo.apply(Transformations::rotateXAroundPointDegrees(-1, Vec3(0, 0, -90)));
        // Ctnovo = Ctnovo.apply(Transformations::rotateXAroundPointDegrees(-1, Vec3(0, 0, -90)));

        cilindro2->update(Cbnovo.getVec3(), Ctnovo.getVec3());
        */

        for (int i = -80; i <= 10; ++i) {

            SDL_Event windowEvent;
            while ( SDL_PollEvent(&windowEvent) ) {
                if (SDL_QUIT == windowEvent.type) { 
                    rodando = false;
                    break; 
                }
            }

            camera->initialize2(Vec3(0, 0, 0), Vec3(i, 0, -dJanela), Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);

            // USAR THREAD PARA RENDERIZAR
            // std::thread renderThread(renderizarCenario, cenario, dJanela, olhoPintor);
            renderizarCenario(cenario, dJanela, olhoPintor);
            // cenario->pintarCanvas(dJanela, olhoPintor);

            // USAR THREAD PARA COLORIR
            // std::thread colorThread(colorirCenario, renderer, cenario, nLin, nCol);
            colorirCenario(renderer, cenario, nLin, nCol);
            // for (int l = 0; l < nLin; ++l) {
            //     for (int c = 0; c < nCol; ++c) {
            //         SDL_Color cor = cenario->canvas->cores[l][c];

            //         SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
            //         SDL_RenderDrawPoint(renderer, c, l); // x = coluna que ta e y = linha que ta
            //     }
            // }

            // renderThread.join();
            // colorThread.join();
        
            // cout << "Fim da pintura" << endl;
            SDL_RenderPresent(renderer); // usar no final para pintar
            if ( window = nullptr ) {
                cout << "ERRO:" << SDL_GetError() << "\n";
                return 1;
            }
        }

    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}
