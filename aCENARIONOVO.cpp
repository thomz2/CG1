// TODO: implementar destrutores nas classes

#include <iostream>
#include <SDL2/SDL.h>
#include <thread>
#include <vector>
#include <utility>
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
#include "classes/headers/primitives/ObjMesh.h"
#include "classes/headers/primitives/mesh/Texture.h"
#include "classes/headers/luzes/LuzPontual.h"
#include "classes/headers/luzes/LuzSpot.h"
#include "classes/headers/luzes/LuzDirecional.h"
#include "classes/headers/primitives/Cluster.h"

#include "classes/miniball/Seb.h"
// typedef double FT;
// typedef Seb::Point<FT> Point;
// typedef std::vector<Point> PointVector;
// typedef Seb::Smallest_enclosing_ball<FT> Miniball;

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

// Função para iniciar o temporizador
void startTimer(std::chrono::steady_clock::time_point& startTime) {
    startTime = std::chrono::steady_clock::now();
}

// Função para obter a contagem de tempo decorrido em milissegundos
long getElapsedTime(const std::chrono::steady_clock::time_point& startTime) {
    auto endTime = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

// Miniball getMiniball(vector<Vec3> pontos) {

//     PointVector S;
//     vector<double> coords(3);
    
//     for (int i = 0; i < pontos.size(); ++i) {
//         coords[0] = pontos[i].x;
//         coords[1] = pontos[i].y;
//         coords[2] = pontos[i].z;
//         S.push_back(Point(3, coords.begin()));
//     }

//     return Miniball(3, S);
// }

int main ( int argc, char *argv[] ) {

    SDL_Window *window; // = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wJanela, hJanela, SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_Renderer *renderer;


    // initializeSDLAndWindow(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    const int XPOSITIVO = 200;
    const int ZPOSITIVO = 200;
    const int YPOSITIVO = 200;

    const double dJanela = 30;
    const double rEsfera = 40;
    const double zCentroEsfera = - (dJanela + rEsfera) - 50; // sempre diminuindo um valor

    Vec3 lookat(56.5685, 230, 106.569);
    // Vec3 lookfrom(-30, 60, 90);
    Vec3 lookfrom(0, 230, 50);

    Camera *camera = new Camera(lookfrom, lookat, Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT, Vec3(0.9, 0.9, 0.9), camera);
    const double wJanela = camera->wJanela, hJanela = camera->hJanela;
    camera->cenario = cenario;
    // camera->changeCamera();

    SDL_Color corVermelha = {255, 0, 0, 255};
    SDL_Color corVerde = {0, 255, 0, 255};
    SDL_Color corAzul = {0, 0, 255, 255};

    Texture* textura = new Texture("assets/snow.png", true);
    Plano* chao = new Plano(5, corAzul, BaseMaterial(Vec3(0.2, 0.7, 0.2), Vec3(0, 0, 0), Vec3(0.2, 0.7, 0.2), 1), Vec3(0, -20 + YPOSITIVO, 0), Vec3(0, 1, 0), textura);


    BaseMaterial materialMesh = BaseMaterial();
    materialMesh.REFLETIVIDADE = Vec3(0.2, 0.2, 0.2);

    // <========== OBJETOS DO CENARIO ==========>
    Cilindro* estacaDaPlaca = new Cilindro(10, corAzul, Vec3(-30 + XPOSITIVO, -20 + YPOSITIVO, -26 + ZPOSITIVO), Vec3(-30 + XPOSITIVO, 75 + YPOSITIVO, -26 + ZPOSITIVO), 3, BaseMaterial(Vec3(88.0, 57.0, 39.0), 1));
    ObjMesh*  placa         = new ObjMesh(11, "assets/placaAmarela/placa_amarela.obj", "assets/placaAmarela/placa.png", materialMesh);
    placa->applyMatrix(Transformations::scale(30, 30, 30));
    placa->applyMatrix(Transformations::shear());
    placa->applyMatrix(Transformations::rotateYAroundPointDegrees(90, Vec3(0, 1, 0)));
    placa->applyMatrix(Transformations::translate(-30 + XPOSITIVO, 70 + YPOSITIVO, -26 + ZPOSITIVO));
    Cone* montanha1 = new Cone(8, corAzul, Vec3(-500 + XPOSITIVO, -20 + YPOSITIVO, -1900 + ZPOSITIVO), Vec3(0, 1, 0), 1500, 800, BaseMaterial(Vec3(0, 153.0/255.0, 51.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));
    Cone* montanha2 = new Cone(9, corAzul, Vec3(500 + XPOSITIVO, -20 + YPOSITIVO, -1850 + ZPOSITIVO), Vec3(0, 1, 0), 1500, 800, BaseMaterial(Vec3(0, 153.0/255.0, 51.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));
    // <========== OBJETOS DO CENARIO ==========>

    // <========== PERSONAGENS ==========>
    ObjMesh* stan = new ObjMesh(6, "assets/stan/stan.obj", "assets/stan/stan_all.png", materialMesh);
    stan->applyMatrix(Transformations::translate(10 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    Cluster* clusterStan = new Cluster(stan, 20000);

    ObjMesh* kyle = new ObjMesh(7, "assets/kyle/kyle.obj", "assets/kyle/kyle_all.png", materialMesh);
    kyle->applyMatrix(Transformations::translate(50 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    Cluster* clusterKyle = new Cluster(kyle, 20000);

    ObjMesh* cartman = new ObjMesh(6, "assets/Cartman/cartman2.obj", "assets/Cartman/cartman_all.png", materialMesh);
    cartman->applyMatrix(Transformations::translate(100 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));

    ObjMesh* kenny = new ObjMesh(8, "assets/kenny/kenny.obj", "assets/kenny/kenny_all.png", materialMesh, false);
    kenny->applyMatrix(Transformations::translate(150 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    Cluster* clusterKenny = new Cluster(kenny, 20000);
    
    ObjMesh* dio = new ObjMesh(7, "assets/dio/DIO.obj", "assets/dio/DIO1.png", materialMesh, true);
    dio->applyMatrix(Transformations::scale(25, 25, 25));
    Cluster* clusterDio = new Cluster(dio, 20000);
    // <========== PERSONAGENS ==========>
    



    // megaman->applyMatrix();

    // mesh2->textura->testColors();

    LuzPontual* luzPontual = new LuzPontual(Vec3(-250 + XPOSITIVO, 125 + YPOSITIVO, 0 + ZPOSITIVO), Vec3(0.2, 0.2, 0.2));
    LuzSpot* luzSpot = new LuzSpot(Vec3(-15 + XPOSITIVO, 50 + YPOSITIVO, -18 + ZPOSITIVO), Vec3(0.3, 0.3, 0.3), Vec3(0, -1, 0).norm(), 60);
    LuzDirecional* luzDirecional = new LuzDirecional(Vec3(0.15, 0.1, 0.1), Vec3(-1, -1, 0).norm());

    // Esfera* esferaTeste = new Esfera(100, corAzul, Vec3(30, 30, -30), 15, BaseMaterial(Vec3(0.8, 0.2, 0.2), Vec3(0.2, 0.2, 0.8), Vec3(0.2, 0.8, 0.2), 10));
    // ObjMesh* cubo = new ObjMesh(8, "assets/cube/cube.obj", "assets/uv_test.png", materialMesh, 1);
    // cubo->applyMatrix(Transformations::scale(50, 50, 50));
    // cubo->applyMatrix(Transformations::translate(10 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    // cubo->applyMatrix(Transformations::shear(0, 0, 0, 0, -1, 0));
    // cenario->objetos.push_back(cubo);


    // cenario->objetos.push_back(clusterDio);

    // cenario->objetos.push_back(clusterStan);
    // cenario->objetos.push_back(clusterKyle);
    // cenario->objetos.push_back(cartman);
    // cenario->objetos.push_back(clusterKenny);

    cenario->objetos.push_back(chao);
    cenario->objetos.push_back(montanha1);
    cenario->objetos.push_back(montanha2);
    cenario->objetos.push_back(estacaDaPlaca);
    cenario->objetos.push_back(placa);
         
    cenario->luzes.push_back(luzDirecional);
    // cenario->luzes.push_back(luzPontual);
    // cenario->luzes.push_back(luzSpot);

    const int nCol = 500;
    const int nLin = 500;
    const double Dx = (double)wJanela / (double)nCol;
    const double Dy = (double)hJanela / (double)nLin;
    cenario->setCanvas(nLin, nCol, Dx, Dy);

    bool rodando = true;
    double i = 0;
    double res = 10;
    while (rodando) {
        SDL_Event windowEvent;
        while ( SDL_PollEvent(&windowEvent) ) {
            if (SDL_QUIT == windowEvent.type) { 
                rodando = false;
                break; 
            }
            else if (windowEvent.type == SDL_KEYDOWN) {
                // Lógica para teclas pressionadas
                switch (windowEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        rodando = false;
                        break;
                    case SDLK_w:
                        // Lógica para mover a câmera para cima
                        camera->moveForward(5);
                        break;
                    case SDLK_s:
                        // Lógica para mover a câmera para baixo
                        camera->moveBackward(5);
                        break;
                    case SDLK_a:
                        // Lógica para mover a câmera para a esquerda
                        camera->moveLeft(5);
                        break;
                    case SDLK_d:
                        // Lógica para mover a câmera para a direita
                        camera->moveRight(5);
                        break;
                    case SDLK_LSHIFT:
                        camera->moveDown(5);
                        break;
                    case SDLK_RSHIFT:
                        camera->moveDown(5);
                        break;
                    case SDLK_SPACE:
                        camera->moveUp(5);
                        break;
                    case SDLK_LEFT:
                        camera->lookLeft(5);
                        break;
                    case SDLK_RIGHT:
                        camera->lookRight(5);
                        break;
                    case SDLK_UP:
                        camera->lookUp(5);
                        break;
                    case SDLK_DOWN:
                        camera->lookDown(5);
                        break;
                    case SDLK_c:
                        camera->changeCamera();
                        break;
                    case SDLK_1:
                        res = 1;
                        break;
                    case SDLK_2:
                        res = 2;
                        break;
                    case SDLK_5:
                        res = 5;
                        break;
                    case SDLK_9:
                        res = 10;
                        break;
                    case SDLK_EQUALS:
                        camera->changeFov(camera->vFov + 1);
                        cout << camera->vFov << endl;
                        break;
                    case SDLK_MINUS:
                        camera->changeFov(camera->vFov - 1);
                        cout << camera->vFov << endl;
                        break;
                }
            }
        }

         std::chrono::steady_clock::time_point timerStart;

    // Inicia o temporizador
    startTimer(timerStart);

    // Alguma lógica de aplicação aqui...



        camera->update();
        camera->renderAndPaintCanvasThread(4, res);
        colorirCenario(renderer, cenario, nLin, nCol);

    // Obtém o tempo decorrido
    long elapsedTime = getElapsedTime(timerStart);
    // std::cout << "Tempo decorrido: " << elapsedTime << " ms\n";
        i+= 2;
        
        SDL_RenderPresent(renderer); // usar para pintar
        if ( window = nullptr ) {
            cout << "ERRO:" << SDL_GetError() << "\n";
            return 1;
        }
    }
    
    // while (rodando) {
        // for (int i = -100; i <= 0 ; i+=5) {

            // SDL_Event windowEvent;
            // while ( SDL_PollEvent(&windowEvent) ) {
            //     if (SDL_QUIT == windowEvent.type) { 
            //         rodando = false;
            //         break;  
            //     }
            // }
    


    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}
