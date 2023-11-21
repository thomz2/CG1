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
#include "classes/headers/primitives/ObjMesh.h"
#include "classes/headers/primitives/mesh/Texture.h"

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

    Vec3 lookat(0, -10, -dJanela);
    Vec3 lookfrom(0, 40, 70);

    Camera *camera = new Camera(lookfrom, lookat, Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT, Vec3(0.5, 0.5, 0.5), camera);
    const double wJanela = camera->wJanela, hJanela = camera->hJanela;
    camera->cenario = cenario;

    SDL_Color corVermelha = {255, 0, 0, 255};
    SDL_Color corVerde = {0, 255, 0, 255};
    SDL_Color corAzul = {0, 0, 255, 255};

    // Mesh* mesh = new Mesh(1);
    // mesh->vertices.push_back(Vec3(0, 0, -dJanela));
    // mesh->vertices.push_back(Vec3(30, 0, -dJanela));
    // mesh->vertices.push_back(Vec3(30, 30, -dJanela));
    // mesh->faces.push_back({ 0,1,2 });
    // mesh->vertices.push_back({ 0,30,-dJanela });
    // mesh->faces.push_back({ 0,2,3 });
    // mesh->renderizar();

    Plano* chao = new Plano(5, corAzul, BaseMaterial(Vec3(0.2, 0.7, 0.2), Vec3(0, 0, 0), Vec3(0.2, 0.7, 0.2), 1), Vec3(0, -20, 0), Vec3(0, 1, 0));
    Plano* planoDeFundo = new Plano(6, corAzul, BaseMaterial(Vec3(0.3, 0.3, 0.7), Vec3(0, 0, 0), Vec3(0.3, 0.3, 0.7), 1), Vec3(0, 0, -200), Vec3(0, 0, 1));


    BaseMaterial materialMesh = BaseMaterial();
    materialMesh.REFLETIVIDADE = Vec3(0.2, 0.2, 0.2);
    // ObjMesh1* mesh2 = new ObjMesh(3, "assets/Yoshi2/Yoshi.obj", "assets/Yoshi/yoshi_all.png", materialMesh);
    // ObjMesh* mesh2 = new ObjMesh(2, "assets/porygon/porygon.obj", "assets/porygon/porygon_body.png", materialMesh);
    // ObjMesh* mesh3 = new ObjMesh(3, "assets/mine_cube/cube.obj", "assets/uv_test.png", materialMesh);
    // mesh3->applyMatrix(Transformations::scale(25, 25, 25));
    // mesh3->applyMatrix(Transformations::translate(0, 0, -50));
    ObjMesh* megaman = new ObjMesh(4, "assets/megaman/megaman.obj", "assets/megaman/Megaman.png", materialMesh);
    megaman->applyMatrix(Transformations::scale(1, 1, 1).apply(Transformations::translate(0, 20, 0)).apply(Transformations::rotateYAroundPoint(135, Vec3(0, 0, 0))));

    ObjMesh* roll = new ObjMesh(5, "assets/roll/roll.obj", "assets/roll/Roll_(Cutscene).png", materialMesh);
    roll->applyMatrix(Transformations::translate(18, 18, -18).apply(Transformations::rotateYAroundPoint(109, Vec3(20, 20, -20))));

    // megaman->applyMatrix();

    // mesh2->textura->testColors();

    Luz* luzPontual = new Luz(Vec3(-40, 25, 0), Vec3(0.8, 0.8, 0.8));

    cenario->objetos.push_back(megaman);
    cenario->objetos.push_back(roll);
    cenario->objetos.push_back(chao);
    cenario->objetos.push_back(planoDeFundo);

    cenario->luzes.push_back(luzPontual);

    const int nCol = 500;
    const int nLin = 500;
    const double Dx = (double)wJanela / (double)nCol;
    const double Dy = (double)hJanela / (double)nLin;
    cenario->setCanvas(nLin, nCol, Dx, Dy);

    bool rodando = true;
    double i = 0;
    while (rodando) {
        // cout << i << endl;
    //     // for (int i = -100; i <= 0 ; i+=5) {

        SDL_Event windowEvent;
        while ( SDL_PollEvent(&windowEvent) ) {
            if (SDL_QUIT == windowEvent.type) { 
                rodando = false;
                break; 
            }
        }

        // mesh2->applyMatrix(Transformations::rotateZAroundPointDegrees(1, Vec3(0, 0, 0)).apply(Transformations::rotateXAroundPointDegrees(1, Vec3(0, 0, 0))));
        // mesh2->applyMatrix(Transformations::translate(0, -i, 0));
        // mesh2->applyMatrix(Transformations::scale(i, i, i));    

        // camera->initialize2(Vec3(i, 0, 50), Vec3(0, 10, -dJanela), Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);
        if (i == 0) {
            camera->renderAndPaintCanvasThread(4, 1);
            colorirCenario(renderer, cenario, nLin, nCol);
        }
        i += 1;
        
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
