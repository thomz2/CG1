// TODO: implementar destrutores nas classes

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

int main ( int argc, char *argv[] ) {

    SDL_Window *window; // = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wJanela, hJanela, SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_Renderer *renderer;

    // initializeSDLAndWindow(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    const int XPOSITIVO = 5000;
    const int ZPOSITIVO = 5000;
    const int YPOSITIVO = 5000;

    const double dJanela = 30;
    const double rEsfera = 40;
    const double zCentroEsfera = - (dJanela + rEsfera) - 50; // sempre diminuindo um valor

    Vec3 lookfrom(4959.57, 5025.9, 5093.83);
    Vec3 lookat(4959.17, 5025.9, 5013.86);

    Camera *camera = new Camera(lookfrom, lookat, Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT, Vec3(0.5, 0.5, 0.6), camera);
    const double wJanela = camera->wJanela, hJanela = camera->hJanela;
    camera->cenario = cenario;

    SDL_Color corVermelha = {255, 0, 0, 255};
    SDL_Color corVerde = {0, 255, 0, 255};
    SDL_Color corAzul = {0, 0, 255, 255};

    BaseMaterial materialMesh = BaseMaterial();
    materialMesh.REFLETIVIDADE = Vec3(0.2, 0.2, 0.2);
    materialMesh.RUGOSIDADE = Vec3(0.1, 0.1, 0.1);
    
    Difuso difuso = Difuso();
    difuso.KAMBIENTE = Vec3(1.0, 0.0, 0.0);

    Metalico metalico = Metalico();
    metalico.KAMBIENTE = Vec3(1.0, 0.0, 0.0);

    Plastico plastico = Plastico();
    plastico.KAMBIENTE = Vec3(1.0, 0.0, 0.0);

    Madeira madeira = Madeira();
    madeira.KAMBIENTE = Vec3(80.0/255.0, 48.0/255.0, 30.0/255.0);

    Pele pele = Pele();
    pele.KAMBIENTE = Vec3(179.0/255.0, 139.0/255.0, 109.0/255.0);

    // <========== CHAO ==========>
    Texture* textura = new Texture("assets/green.png", true);
    Plano* chao = new Plano(5, corAzul, BaseMaterial(Vec3(0.2, 0.7, 0.2), Vec3(0, 0, 0), Vec3(0.2, 0.7, 0.2), 1), Vec3(0, -20 + YPOSITIVO, 0), Vec3(0, 1, 0), textura);
    cenario->objetos.push_back(chao);
    // <========== CHAO ==========>

    // <========== Espelho ==========>
    // Esfera* espelho = new Esfera(601, corAzul, Vec3(-40 + XPOSITIVO, 35 + YPOSITIVO, -18 + ZPOSITIVO), 30);
    Esfera* espelho = new Esfera(601, corAzul, Vec3(0 + XPOSITIVO, 35 + YPOSITIVO, 0 + ZPOSITIVO), 30);
    espelho->ehReflexivo = true;
    cenario->objetos.push_back(espelho);
    // <========== Espelho ==========>

    // <========== PERSONAGENS ==========>
    ObjMesh* stan = new ObjMesh(6, "assets/stan/stan.obj", "assets/stan/stan_all.png", difuso);
    stan->applyMatrix(Transformations::translate(-40 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    stan->ehReflexivo = true;
    Cluster* clusterStan = new Cluster(stan, 20000, true);
    cenario->objetos.push_back(clusterStan);
    // <========== PERSONAGENS ==========>
    
    // <========== LUZES ==========>
    LuzPontual* luzPontual = new LuzPontual(Vec3(-550 + XPOSITIVO, 7500 + YPOSITIVO, -18 + ZPOSITIVO), Vec3(0.2, 0.2, 0.2));
    LuzDirecional* luzDirecional = new LuzDirecional(Vec3(0.1, 0.1, 0.1), Vec3(-1, -1, 0).norm());

    luzPontual->ignorar = true;

    cenario->luzes.push_back(luzDirecional);
    // cenario->luzes.push_back(luzPontual);
    // <========== LUZES ==========>

    const int nCol = 500;
    const int nLin = 500;
    const double Dx = (double)wJanela / (double)nCol;
    const double Dy = (double)hJanela / (double)nLin;
    cenario->setCanvas(nLin, nCol, Dx, Dy);

    bool rodando = true;
    bool retrato = false;
    bool temporizer = false;
    double i = 0;
    double res = 10;
    double vel = 5;
    while (rodando) {
        SDL_Event windowEvent;
        while ( SDL_PollEvent(&windowEvent) ) {
            if (SDL_QUIT == windowEvent.type) { 
                rodando = false;
                break; 
            }
            else if (windowEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (windowEvent.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = windowEvent.button.x;
                    int mouseY = windowEvent.button.y;

                    camera->pick(mouseY, mouseX);

                    // SDL_Log("Posição do mouse ao clicar: (%d, %d)", mouseX, mouseY);
                }
            }
            else if (windowEvent.type == SDL_KEYDOWN) {
                // Lógica para teclas pressionadas
                switch (windowEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        rodando = false;
                        break;
                    case SDLK_w:
                        // Lógica para mover a câmera para cima
                        camera->moveForward(vel);
                        break;
                    case SDLK_s:
                        // Lógica para mover a câmera para baixo
                        camera->moveBackward(vel);
                        break;
                    case SDLK_a:
                        // Lógica para mover a câmera para a esquerda
                        camera->moveLeft(vel);
                        break;
                    case SDLK_d:
                        // Lógica para mover a câmera para a direita
                        camera->moveRight(vel);
                        break;
                    case SDLK_LSHIFT:
                        camera->moveDown(vel);
                        break;
                    case SDLK_RSHIFT:
                        camera->moveDown(vel);
                        break;
                    case SDLK_SPACE:
                        camera->moveUp(vel);
                        break;
                    case SDLK_LEFT:
                        camera->lookLeft(vel);
                        break;
                    case SDLK_RIGHT:
                        camera->lookRight(vel);
                        break;
                    case SDLK_UP:
                        camera->lookUp(vel);
                        break;
                    case SDLK_DOWN:
                        camera->lookDown(vel);
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
                        break;
                    case SDLK_MINUS:
                        camera->changeFov(camera->vFov - 1);
                        break;
                    case SDLK_r:
                        retrato = !retrato;
                        cout << "MODO RETRATO " << (retrato? "LIGADO" : "DESLIGADO") << endl;
                        break;
                    case SDLK_COMMA:
                        vel /= 2;
                        cout << "NOVA VELOCIDADE: " << vel << endl;
                        break;
                    case SDLK_PERIOD:
                        vel *= 2;
                        cout << "NOVA VELOCIDADE: " << vel << endl;
                        break;
                    case SDLK_m:{
                        camera->tempo = !camera->tempo;
                        if (camera->tempo) {
                            luzPontual->ignorar = false;
                            cenario->luzAmbiente = Vec3(0.7, 0.7, 0.79);

                            // ilumPost1->luzSpot->ignorar = true;
                            // ilumPost2->luzSpot->ignorar = true;
                            // ilumPost3->luzSpot->ignorar = true;
                            // ilumPost4->luzSpot->ignorar = true;
                            luzDirecional->ignorar = true;
                        } else {
                            luzPontual->ignorar = true;

                            cenario->luzAmbiente = Vec3(0.5, 0.5, 0.6);
                            // ilumPost1->luzSpot->ignorar = false;
                            // ilumPost2->luzSpot->ignorar = false;
                            // ilumPost3->luzSpot->ignorar = false;
                            // ilumPost4->luzSpot->ignorar = false;
                            luzDirecional->ignorar = false;
                        }
                        break;
                    }
                    case SDLK_t: {
                        temporizer = !temporizer;
                        cout << "TEMPORIZADOR " << (temporizer? "LIGADO" : "DESLIGADO") << endl;
                    }
                }
            }
        }

        std::chrono::steady_clock::time_point timerStart;

        if (!retrato){

            // Inicia o temporizador
            startTimer(timerStart);

            camera->update();
            camera->renderAndPaintCanvasThread(4, res);
            colorirCenario(renderer, cenario, nLin, nCol);

            // Obtém o tempo decorrido
            long elapsedTime = getElapsedTime(timerStart);
            if (temporizer)
                std::cout << "Tempo de renderizacao: " << elapsedTime << " ms\n";
        }
        i+= 2;

        
        SDL_RenderPresent(renderer); // usar para pintar
        if ( window = nullptr ) {
            cout << "ERRO:" << SDL_GetError() << "\n";
            return 1;
        }
    }
    
    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}
