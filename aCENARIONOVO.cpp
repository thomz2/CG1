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

    const int XPOSITIVO = 5000;
    const int ZPOSITIVO = 5000;
    const int YPOSITIVO = 5000;

    const double dJanela = 30;
    const double rEsfera = 40;
    const double zCentroEsfera = - (dJanela + rEsfera) - 50; // sempre diminuindo um valor

    Vec3 lookat(5075.08, 5017.95, 5041.74);
    // Vec3 lookfrom(-30, 60, 90);
    Vec3 lookfrom(5075, 5017.87, 5121.74);

    Camera *camera = new Camera(lookfrom, lookat, Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT, Vec3(0.5, 0.5, 0.5), camera);
    const double wJanela = camera->wJanela, hJanela = camera->hJanela;
    camera->cenario = cenario;
    // camera->changeCamera();

    SDL_Color corVermelha = {255, 0, 0, 255};
    SDL_Color corVerde = {0, 255, 0, 255};
    SDL_Color corAzul = {0, 0, 255, 255};

    BaseMaterial materialMesh = BaseMaterial();
    materialMesh.REFLETIVIDADE = Vec3(0.2, 0.2, 0.2);
    materialMesh.RUGOSIDADE = Vec3(0.1, 0.1, 0.1);
    
    Texture* textura = new Texture("assets/snow.png", true);
    Plano* chao = new Plano(5, corAzul, BaseMaterial(Vec3(0.2, 0.7, 0.2), Vec3(0, 0, 0), Vec3(0.2, 0.7, 0.2), 1), Vec3(0, -20 + YPOSITIVO, 0), Vec3(0, 1, 0), textura);

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


    // <========== OBJETOS DO CENARIO ==========>
    Cilindro* estacaDaPlaca = new Cilindro(10, corAzul, Vec3(-30 + XPOSITIVO, -20 + YPOSITIVO, -26 + ZPOSITIVO), Vec3(-30 + XPOSITIVO, 75 + YPOSITIVO, -26 + ZPOSITIVO), 3, metalico);
    ObjMesh*  placa         = new ObjMesh(11, "assets/placaAmarela/placa_amarela.obj", "assets/placaAmarela/placa.png", materialMesh);
    placa->applyMatrix(Transformations::scale(30, 30, 30));
    placa->applyMatrix(Transformations::shear());
    placa->applyMatrix(Transformations::rotateYAroundPointDegrees(90, Vec3(0, 1, 0)));
    placa->applyMatrix(Transformations::translate(-30 + XPOSITIVO, 70 + YPOSITIVO, -26 + ZPOSITIVO));
    
    ObjMesh* rua = new ObjMesh(12, "assets/rua/rua.obj", "assets/rua/RUA.png", materialMesh);
    rua->applyMatrix(Transformations::scale(200, 20, 80));
    rua->applyMatrix(Transformations::translate(0 + XPOSITIVO, -17 + YPOSITIVO, 210 + ZPOSITIVO));
    // <========== OBJETOS DO CENARIO ==========>


    Cone* montanha1 = new Cone(8, corAzul, Vec3(-500 + XPOSITIVO, -20 + YPOSITIVO, -2400 + ZPOSITIVO), Vec3(0, 1, 0), 2500, 2000, BaseMaterial(Vec3(0, 53.0/255.0, 1.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));
    Cone* montanha2 = new Cone(9, corAzul, Vec3(500 + XPOSITIVO, -20 + YPOSITIVO, -2350 + ZPOSITIVO), Vec3(0, 1, 0), 2500, 2000, BaseMaterial(Vec3(0, 53.0/255.0, 1.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));


    // <========== ESTRUTURAS ==========>
    ObjMesh* predioBegeClaro = new ObjMesh(100, "assets/predios/predioroxo.obj", "assets/predios/predioroxo.png", materialMesh);
    predioBegeClaro->applyMatrix(Transformations::rotateYByDegree(180));
    predioBegeClaro->applyMatrix(Transformations::scale(50, 50, 50));
    predioBegeClaro->applyMatrix(Transformations::translate(-50 + XPOSITIVO, -15 + YPOSITIVO, 500 + ZPOSITIVO));

    ObjMesh* predioMarrom = new ObjMesh(101, "assets/predios/predioamarelo.obj", "assets/predios/predioamarelo.png", materialMesh);
    predioMarrom->applyMatrix(Transformations::rotateYByDegree(180));
    predioMarrom->applyMatrix(Transformations::scale(50, 50, 50));
    predioMarrom->applyMatrix(Transformations::translate(250 + XPOSITIVO, -15 + YPOSITIVO, 500 + ZPOSITIVO));

    ObjMesh* predioTom = new ObjMesh(101, "assets/predios/prediotom.obj", "assets/predios/prediotom.png", materialMesh);
    predioTom->applyMatrix(Transformations::rotateYByDegree(180));
    predioTom->applyMatrix(Transformations::scale(50, 50, 50));
    predioTom->applyMatrix(Transformations::translate(610 + XPOSITIVO, -15 + YPOSITIVO, 500 + ZPOSITIVO));
    // <========== ESTRUTURAS ==========>

    // <========== ARVORES ==========>
    BaseMaterial materialCone = BaseMaterial(madeira.RUGOSIDADE, madeira.REFLETIVIDADE, Vec3(0, 55.0/255.0, 0), madeira.M);
    
    Cilindro* tronco1 = new Cilindro(601, corAzul, Vec3(XPOSITIVO, YPOSITIVO, ZPOSITIVO - 350), Vec3(XPOSITIVO, YPOSITIVO + 140, ZPOSITIVO - 350), 30, madeira);
    Cone*     cone1   = new Cone(602, corAzul, tronco1->Ct, tronco1->Ct.add(Vec3(0, 200, 0)), 100, materialCone);
    // <========== ARVORES ==========>

    // <========== POSTES ==========>
    BaseMaterial materialLampada = BaseMaterial();
    materialLampada.KAMBIENTE = Vec3(253.0/255.0, 253.0/255.0, 150/255.0);

    Metalico materialPoste = Metalico();
    materialPoste.KAMBIENTE = Vec3(0, 0, 0); 

    EsferaDeLuzSpot* ilumPost = new EsferaDeLuzSpot(701, corAzul, Vec3(XPOSITIVO + 60, YPOSITIVO + 170, ZPOSITIVO - 20), 20, materialLampada, Vec3(253.0/255.0, 253.0/255.0, 150/255.0), 11);
    Cilindro*        poste    = new Cilindro(702, corAzul, Vec3(XPOSITIVO + 60, YPOSITIVO - 20, ZPOSITIVO - 20), Vec3(XPOSITIVO + 60, YPOSITIVO + 150, ZPOSITIVO - 20), 6, materialPoste);
    // <========== POSTES ==========>

    // <========== PERSONAGENS ==========>
    ObjMesh* stan = new ObjMesh(6, "assets/stan/stan.obj", "assets/stan/stan_all.png", difuso);
    stan->applyMatrix(Transformations::translate(10 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    Cluster* clusterStan = new Cluster(stan, 20000, true);



    Esfera* esfStan = new Esfera(1999, corAzul, Vec3(10 + XPOSITIVO, 50 + YPOSITIVO, -18 + ZPOSITIVO), 20, pele);
    cout << esfStan->PCentro << endl;
    Esfera* testeEspelho = new Esfera(1998, corAzul, 
        Vec4(esfStan->PCentro).apply(Transformations::reflection(Vec3(0, 0, -1), Vec3(10 + XPOSITIVO, 50 + YPOSITIVO, 20 + ZPOSITIVO ))).getVec3(), 20, pele );
    cout << testeEspelho->PCentro << endl;

    ObjMesh* kyle = new ObjMesh(7, "assets/kyle/kyle.obj", "assets/kyle/kyle_all.png", metalico);
    kyle->applyMatrix(Transformations::translate(50 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    Cluster* clusterKyle = new Cluster(kyle, 20000, true);

    Esfera* esfKyle= new Esfera(2999, corAzul, Vec3(50 + XPOSITIVO, 50 + YPOSITIVO, -18 + ZPOSITIVO), 20, metalico);


    ObjMesh* cartman = new ObjMesh(8, "assets/Cartman/cartman2.obj", "assets/Cartman/cartman_all.png", plastico);
    cartman->applyMatrix(Transformations::translate(100 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));

    Esfera* esfCartman = new Esfera(3999, corAzul, Vec3(100 + XPOSITIVO, 50 + YPOSITIVO, -18 + ZPOSITIVO), 20, plastico);



    ObjMesh* kenny = new ObjMesh(9, "assets/kenny/kenny.obj", "assets/kenny/kenny_all.png", madeira, false);
    kenny->applyMatrix(Transformations::translate(150 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    Cluster* clusterKenny = new Cluster(kenny, 20000, true);
    
    Esfera* esfKenny = new Esfera(4999, corAzul, Vec3(150 + XPOSITIVO, 50 + YPOSITIVO, -18 + ZPOSITIVO), 20, madeira);

    ObjMesh* dio = new ObjMesh(7, "assets/dio/DIO.obj", "assets/dio/DIO1.png", materialMesh, true);
    dio->applyMatrix(Transformations::scale(25, 25, 25));
    Cluster* clusterDio = new Cluster(dio, 20000, true);
    // <========== PERSONAGENS ==========>
    



    // megaman->applyMatrix();

    // mesh2->textura->testColors();

    LuzPontual* luzPontual = new LuzPontual(Vec3(50 + XPOSITIVO, 325 + YPOSITIVO, -18 + ZPOSITIVO), Vec3(0.8, 0.8, 0.8));
    LuzSpot* luzSpot = new LuzSpot(Vec3(-15 + XPOSITIVO, 50 + YPOSITIVO, -18 + ZPOSITIVO), Vec3(0.3, 0.3, 0.3), Vec3(0, -1, 0).norm(), 60);
    LuzDirecional* luzDirecional = new LuzDirecional(Vec3(0.1, 0.1, 0.2), Vec3(-1, -1, 0).norm());

    // Esfera* esferaTeste = new Esfera(100, corAzul, Vec3(30, 30, -30), 15, BaseMaterial(Vec3(0.8, 0.2, 0.2), Vec3(0.2, 0.2, 0.8), Vec3(0.2, 0.8, 0.2), 10));
    // ObjMesh* cubo = new ObjMesh(8, "assets/cube/cube.obj", "assets/uv_test.png", materialMesh, 1);
    // cubo->applyMatrix(Transformations::scale(50, 50, 50));
    // cubo->applyMatrix(Transformations::translate(10 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    // cubo->applyMatrix(Transformations::shear(0, 0, 0, 0, -1, 0));
    // cenario->objetos.push_back(cubo);


    // cenario->objetos.push_back(clusterDio);

    // cenario->objetos.push_back(clusterStan);
    // cenario->objetos.push_back(esfStan);
    cenario->objetos.push_back(tronco1);
    cenario->objetos.push_back(cone1);
    cenario->objetos.push_back(ilumPost);
    cenario->objetos.push_back(poste);
    // cenario->objetos.push_back(testeEspelho);
    cenario->objetos.push_back(clusterKyle);
    // cenario->objetos.push_back(esfKyle);
    // cenario->objetos.push_back(cartman);
    // cenario->objetos.push_back(esfCartman);
    // cenario->objetos.push_back(clusterKenny);
    // cenario->objetos.push_back(esfKenny);

    cenario->objetos.push_back(chao);
    // cenario->objetos.push_back(montanha1);
    // cenario->objetos.push_back(montanha2);
    cenario->objetos.push_back(estacaDaPlaca);
    // cenario->objetos.push_back(rua);


    // cenario->objetos.push_back(placa);
    // cenario->objetos.push_back(predioBegeClaro);
    // cenario->objetos.push_back(predioMarrom);
    // cenario->objetos.push_back(predioTom);

    // cenario->luzes.push_back(luzDirecional);
    // cenario->luzes.push_back(luzPontual);
    // cenario->luzes.push_back(luzSpot);
    cenario->luzes.push_back(ilumPost->luzSpot);

    const int nCol = 500;
    const int nLin = 500;
    const double Dx = (double)wJanela / (double)nCol;
    const double Dy = (double)hJanela / (double)nLin;
    cenario->setCanvas(nLin, nCol, Dx, Dy);

    bool rodando = true;
    bool retrato = false;
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
                        int opcao = 0;
                        cout << "MENU:\n";
                        cout << "  [0] FAZER NADA\n";
                        cout << "  [1] TROCAR DIA/NOITE\n";
                        cin >> opcao;
                        switch (opcao)
                        {
                        case 1:
                            camera->tempo = !camera->tempo;
                            break;
                        
                        default:
                            break;
                        }
                        break;
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
            // std::cout << "Tempo decorrido: " << elapsedTime << " ms\n";
        }
        i+= 2;

        // renderText(renderer, font, "Hello, SDL!", 100, 100, textColor);
        
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
