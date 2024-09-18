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

    Vec3 lookfrom(4694, 5035.9, 4849.83);
    Vec3 lookat(4701.17, 5035.9, 4769.36);

    Camera *camera = new Camera(lookfrom, lookat, Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT, Vec3(0.5, 0.5, 0.6), camera);
    const double wJanela = camera->wJanela, hJanela = camera->hJanela;
    camera->cenario = cenario;
    // camera->changeCamera();

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
    Texture* textura = new Texture("assets/snow.png", true);
    Plano* chao = new Plano(5, corAzul, BaseMaterial(Vec3(0.2, 0.7, 0.2), Vec3(0, 0, 0), Vec3(0.2, 0.7, 0.2), 1), Vec3(0, -20 + YPOSITIVO, 0), Vec3(0, 1, 0), textura);
    cenario->objetos.push_back(chao);
    // <========== CHAO ==========>

    // <========== OBJETOS DO CENARIO ==========>
    Cilindro* estacaDaPlaca = new Cilindro(10, corAzul, Vec3(-80 + XPOSITIVO, -20 + YPOSITIVO, -26 + ZPOSITIVO), Vec3(-80 + XPOSITIVO, 75 + YPOSITIVO, -26 + ZPOSITIVO), 3, madeira);
    ObjMesh*  placa         = new ObjMesh(11, "assets/placaAmarela/placa_amarela.obj", "assets/placaAmarela/placa.png", metalico);
    placa->applyMatrix(Transformations::scale(30, 30, 30));
    placa->applyMatrix(Transformations::rotateYAroundPointDegrees(90, Vec3(0, 1, 0)));
    placa->applyMatrix(Transformations::translate(-80 + XPOSITIVO, 70 + YPOSITIVO, -26 + ZPOSITIVO));
    
    // cenario->objetos.push_back(estacaDaPlaca);
    // cenario->objetos.push_back(placa);

    ObjMesh* rua = new ObjMesh(12, "assets/rua/rua.obj", "assets/rua/RUA.png", difuso);
    rua->applyMatrix(Transformations::scale(242, 20, 80));
    rua->applyMatrix(Transformations::translate(0 + XPOSITIVO, -17 + YPOSITIVO, 210 + ZPOSITIVO));
    
    // cenario->objetos.push_back(rua);
    // <========== OBJETOS DO CENARIO ==========>

    // <========== MONTANHAS ==========>
    Cone* montanha1 = new Cone(8, corAzul, Vec3(-500 + XPOSITIVO, -20 + YPOSITIVO, -2400 + ZPOSITIVO), Vec3(0, 1, 0), 2500, 2000, BaseMaterial(Vec3(0, 53.0/255.0, 1.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));
    Cone* montanha2 = new Cone(9, corAzul, Vec3(500 + XPOSITIVO, -20 + YPOSITIVO, -2275 + ZPOSITIVO), Vec3(0, 1, 0), 2500, 2000, BaseMaterial(Vec3(0, 53.0/255.0, 1.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));
    Cone* montanha3 = new Cone(9, corAzul, Vec3(700 + XPOSITIVO, -20 + YPOSITIVO, 2550 + ZPOSITIVO), Vec3(0, 1, 0), 2300, 1800, BaseMaterial(Vec3(0, 53.0/255.0, 1.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));
    Cone* montanha4 = new Cone(9, corAzul, Vec3(-600 + XPOSITIVO, -20 + YPOSITIVO, 2450 + ZPOSITIVO), Vec3(0, 1, 0), 2300, 1800, BaseMaterial(Vec3(0, 53.0/255.0, 1.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));

    Cone* montanha5 = new Cone(9, corAzul, Vec3(3700 - 1300 + XPOSITIVO, -20 + YPOSITIVO, -1200 + ZPOSITIVO), Vec3(0, 1, 0), 2500, 2000, BaseMaterial(Vec3(0, 53.0/255.0, 1.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));
    Cone* montanha6 = new Cone(9, corAzul, Vec3(-3700 + 1250 + XPOSITIVO, -20 + YPOSITIVO, -1350 + ZPOSITIVO), Vec3(0, 1, 0), 2500, 2000, BaseMaterial(Vec3(0, 53.0/255.0, 1.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));
    Cone* montanha7 = new Cone(9, corAzul, Vec3(3700 - 1100 + XPOSITIVO, -20 + YPOSITIVO, 1200 + ZPOSITIVO), Vec3(0, 1, 0), 2500, 2000, BaseMaterial(Vec3(0, 53.0/255.0, 1.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));
    Cone* montanha8 = new Cone(9, corAzul, Vec3(-3800 + 1300 + XPOSITIVO, -20 + YPOSITIVO, 1200 + ZPOSITIVO), Vec3(0, 1, 0), 2500, 2000, BaseMaterial(Vec3(0, 53.0/255.0, 1.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));

    // cenario->objetos.push_back(montanha1);
    // cenario->objetos.push_back(montanha2);
    // cenario->objetos.push_back(montanha3);
    // cenario->objetos.push_back(montanha4);
    // cenario->objetos.push_back(montanha5);
    // cenario->objetos.push_back(montanha6);
    // cenario->objetos.push_back(montanha7);
    // cenario->objetos.push_back(montanha8);  
    // <========== MONTANHAS ==========>

    // <========== ESTRUTURAS ==========>
    ObjMesh* predioBegeClaro = new ObjMesh(100, "assets/predios/predioroxo.obj", "assets/predios/predioroxo.png", difuso);
    predioBegeClaro->applyMatrix(Transformations::rotateYByDegree(180));
    predioBegeClaro->applyMatrix(Transformations::scale(50, 50, 50));
    predioBegeClaro->applyMatrix(Transformations::translate(-275 + XPOSITIVO, -15 + YPOSITIVO, 550 + ZPOSITIVO));

    ObjMesh* predioMarrom = new ObjMesh(101, "assets/predios/predioamarelo.obj", "assets/predios/predioamarelo.png", difuso);
    predioMarrom->applyMatrix(Transformations::rotateYByDegree(180));
    predioMarrom->applyMatrix(Transformations::scale(50, 50, 50));
    predioMarrom->applyMatrix(Transformations::translate(75 + XPOSITIVO, -15 + YPOSITIVO, 550 + ZPOSITIVO));

    ObjMesh* predioTom = new ObjMesh(101, "assets/predios/prediotom.obj", "assets/predios/prediotom.png", difuso);
    predioTom->applyMatrix(Transformations::rotateYByDegree(180));
    predioTom->applyMatrix(Transformations::scale(50, 50, 50));
    predioTom->applyMatrix(Transformations::translate(435 + XPOSITIVO, -15 + YPOSITIVO, 550 + ZPOSITIVO));
    // <========== ESTRUTURAS ==========>

    // <========== SNOWMAN ==========>
    BaseMaterial materialCenoura = BaseMaterial(madeira.RUGOSIDADE, madeira.REFLETIVIDADE, Vec3(1.0, 165.0/255.0, 0), madeira.M);
    BaseMaterial materialNeve = BaseMaterial(madeira.RUGOSIDADE, madeira.REFLETIVIDADE, Vec3(0, 55.0/255.0, 0), madeira.M);
    BaseMaterial materialOlho = BaseMaterial(madeira.RUGOSIDADE, madeira.REFLETIVIDADE, Vec3(0, 0, 0), madeira.M);

    Esfera* bolaBaixo = new Esfera(601, corAzul, Vec3(XPOSITIVO - 300, YPOSITIVO + 10, ZPOSITIVO - 250), 30);
    Esfera* bolaCima  = new Esfera(602, corAzul, Vec3(XPOSITIVO - 300, YPOSITIVO + 55, ZPOSITIVO - 250), 17);
    Cone*   cenoura   = new Cone(603, corAzul, Vec3(XPOSITIVO - 300, YPOSITIVO + 55, ZPOSITIVO - 235), Vec3(XPOSITIVO - 300, YPOSITIVO + 55, ZPOSITIVO - 221), 3, materialCenoura);
    Esfera* olhoEsq   = new Esfera(604, corAzul, Vec3(XPOSITIVO -307, YPOSITIVO + 63, ZPOSITIVO - 238), 3, materialOlho);
    Esfera* olhoDir   = new Esfera(604, corAzul, Vec3(XPOSITIVO -293, YPOSITIVO + 61, ZPOSITIVO - 238), 3, materialOlho);

    cenario->objetos.push_back(bolaBaixo);
    cenario->objetos.push_back(bolaCima);
    cenario->objetos.push_back(cenoura);
    cenario->objetos.push_back(olhoEsq);
    cenario->objetos.push_back(olhoDir);
    // <========== SNOWMAN ==========>

    // <========== POSTES ==========>
    BaseMaterial materialLampada = BaseMaterial();
    materialLampada.KAMBIENTE = Vec3(253.0/255.0, 253.0/255.0, 150/255.0);

    Metalico materialPoste = Metalico();
    materialPoste.KAMBIENTE = Vec3(0, 0, 0); 

    EsferaDeLuzSpot* ilumPost1 = new EsferaDeLuzSpot(701, corAzul, Vec3(XPOSITIVO - 400, YPOSITIVO + 170, ZPOSITIVO + 15), 20, materialLampada, Vec3(0.3, 0.3, 0.3), 11);
    Cilindro*        poste1    = new Cilindro(702, corAzul, Vec3(XPOSITIVO - 400, YPOSITIVO - 20, ZPOSITIVO + 15), Vec3(XPOSITIVO - 400, YPOSITIVO + 150, ZPOSITIVO + 15), 6, materialPoste);

    // cenario->objetos.push_back(ilumPost1);
    // cenario->objetos.push_back(poste1);
    cenario->luzes.push_back(ilumPost1->luzSpot);

    Vec3 pontEspelho2 = Vec4(Vec3(XPOSITIVO - 400, YPOSITIVO - 20, ZPOSITIVO + 15)).apply(Transformations::reflection(Vec3(0, 0, -1), Vec3(XPOSITIVO, 4983, 5210))).getVec3();
    cout << pontEspelho2 << endl;

    EsferaDeLuzSpot* ilumPost2 = new EsferaDeLuzSpot(703, corAzul, pontEspelho2.add(Vec3(0, 190, 0)), 20, materialLampada, Vec3(0.3, 0.3, 0.3), 11);
    Cilindro*        poste2    = new Cilindro(704, corAzul, pontEspelho2, pontEspelho2.add(Vec3(0, 170, 0)), 6, materialPoste);

    // cenario->objetos.push_back(ilumPost2);
    // cenario->objetos.push_back(poste2);
    cenario->luzes.push_back(ilumPost2->luzSpot);

    Vec3 pontEspelho3 = Vec4(pontEspelho2).apply(Transformations::reflection(Vec3(-1, 0, 0), Vec3(5000, 4983, 5210))).getVec3();
    EsferaDeLuzSpot* ilumPost3 = new EsferaDeLuzSpot(703, corAzul, pontEspelho3.add(Vec3(100, 190, 0)), 20, materialLampada, Vec3(0.3, 0.3, 0.3), 11);
    Cilindro*        poste3    = new Cilindro(704, corAzul, pontEspelho3.add(Vec3(100, 0, 0)), pontEspelho3.add(Vec3(100, 170, 0)), 6, materialPoste);

    // cenario->objetos.push_back(ilumPost3);
    // cenario->objetos.push_back(poste3);
    cenario->luzes.push_back(ilumPost3->luzSpot);

    Vec3 pontEspelho4 = Vec4(Vec3(XPOSITIVO - 400, YPOSITIVO - 20, ZPOSITIVO + 15)).apply(Transformations::reflection(Vec3(-1, 0, 0), Vec3(5000, 4983, 5210))).getVec3();
    EsferaDeLuzSpot* ilumPost4 = new EsferaDeLuzSpot(703, corAzul, pontEspelho4.add(Vec3(100, 190, 0)), 20, materialLampada, Vec3(0.3, 0.3, 0.3), 11);
    Cilindro*        poste4    = new Cilindro(704, corAzul, pontEspelho4.add(Vec3(100, 0, 0)), pontEspelho4.add(Vec3(100, 170, 0)), 6, materialPoste);

    // cenario->objetos.push_back(ilumPost4);
    // cenario->objetos.push_back(poste4);
    cenario->luzes.push_back(ilumPost4->luzSpot);
    // <========== POSTES ==========>

    // <========== PERSONAGENS ==========>
    ObjMesh* stan = new ObjMesh(6, "assets/stan/stan.obj", "assets/stan/stan_all.png", difuso);
    stan->applyMatrix(Transformations::translate(-40 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    Cluster* clusterStan = new Cluster(stan, 20000, true);
    // cenario->objetos.push_back(clusterStan);

    ObjMesh* kyle = new ObjMesh(7, "assets/kyle/kyle.obj", "assets/kyle/kyle_all.png", metalico);
    kyle->applyMatrix(Transformations::translate(0 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    Cluster* clusterKyle = new Cluster(kyle, 20000, true);
    // cenario->objetos.push_back(clusterKyle);

    ObjMesh* cartman = new ObjMesh(8, "assets/Cartman/cartman2.obj", "assets/Cartman/cartman_all.png", plastico);
    cartman->applyMatrix(Transformations::translate(50 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    // cenario->objetos.push_back(cartman);

    ObjMesh* kenny = new ObjMesh(9, "assets/kenny/kenny.obj", "assets/kenny/kenny_all.png", madeira, false);
    kenny->applyMatrix(Transformations::translate(100 + XPOSITIVO, -20 + YPOSITIVO, -18 + ZPOSITIVO));
    Cluster* clusterKenny = new Cluster(kenny, 20000, true);
    // cenario->objetos.push_back(clusterKenny);
    
    ObjMesh* dio = new ObjMesh(7, "assets/dio/DIO.obj", "assets/dio/DIO1.png", materialMesh, true);
    dio->applyMatrix(Transformations::scale(25, 25, 25));
    Cluster* clusterDio = new Cluster(dio, 20000, true);
    // <========== PERSONAGENS ==========>
    
    // <========== LUZES ==========>
    LuzPontual* luzPontual = new LuzPontual(Vec3(-550 + XPOSITIVO, 7500 + YPOSITIVO, -18 + ZPOSITIVO), Vec3(0.2, 0.2, 0.2));
    LuzDirecional* luzDirecional = new LuzDirecional(Vec3(0.1, 0.1, 0.1), Vec3(-1, -1, 0).norm());

    luzPontual->ignorar = true;

    cenario->luzes.push_back(luzDirecional);
    cenario->luzes.push_back(luzPontual);
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

                            ilumPost1->luzSpot->ignorar = true;
                            ilumPost2->luzSpot->ignorar = true;
                            ilumPost3->luzSpot->ignorar = true;
                            ilumPost4->luzSpot->ignorar = true;
                            luzDirecional->ignorar = true;
                        } else {
                            luzPontual->ignorar = true;

                            cenario->luzAmbiente = Vec3(0.5, 0.5, 0.6);
                            ilumPost1->luzSpot->ignorar = false;
                            ilumPost2->luzSpot->ignorar = false;
                            ilumPost3->luzSpot->ignorar = false;
                            ilumPost4->luzSpot->ignorar = false;
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
