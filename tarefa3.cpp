// TODO: implementar destrutores nas classes

#include <iostream>
#include <SDL2/SDL.h>
#include "classes/headers/math/Vec3.h"
#include "classes/headers/primitives/Esfera.h"
#include "classes/headers/primitives/Cilindro.h"
#include "classes/headers/primitives/Cone.h"
#include "classes/headers/Canvas.h"
#include "classes/headers/Ray.h"
#include "classes/headers/Scene.h"
#include "classes/headers/materiais/BaseMaterial.h"
#include "classes/headers/materiais/MaterialTarefa.h"

using namespace std;

const int WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;

int main ( int argc, char *argv[] ) {

    SDL_Window *window; // = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wJanela, hJanela, SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_Renderer *renderer;

    const int wJanela = 60, hJanela = 60;

    // initializeSDLAndWindow(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT, Vec3(0.3, 0.3, 0.3));

    const double dJanela = 30;
    const double rEsfera = 40;
    const double zCentroEsfera = - (dJanela + rEsfera) - 50; // sempre diminuindo um valor

    Vec3 centroJanela(0, 0, -dJanela);
    Vec3 olhoPintor(0, 0, 0);

    SDL_Color corVermelha = {255, 0, 0, 255};
    SDL_Color corVerde = {0, 255, 0, 255};
    SDL_Color corAzul = {0, 0, 255, 255};

    Esfera* esfera = new Esfera(0, corVermelha, Vec3(0, 0, -100), rEsfera, MaterialTarefa());
    Plano* chao = new Plano(5, corAzul, BaseMaterial(Vec3(0.2, 0.7, 0.2), Vec3(0, 0, 0), Vec3(0.2, 0.7, 0.2), 1), Vec3(0, -55, 0), Vec3(0, 1, 0));
    Plano* planoDeFundo = new Plano(6, corVerde, BaseMaterial(Vec3(0.3, 0.3, 0.7), Vec3(0, 0, 0), Vec3(0.3, 0.3, 0.7), 1), Vec3(0, 0, -200), Vec3(0, 0, 1));
    
    // Cilindro* cilindro = new Cilindro(1, cor2, Vec3(0, 0, zCentroEsfera), Vec3(500, 0, zCentroEsfera), 250);
    // Esfera* esfera2 = new Esfera(1, corEsfera2, Vec3(0, 1, zCentroEsfera), rEsfera - 30);
    // Cone* cone = new Cone(2, corVerde, Vec3(0, 0, zCentroEsfera), Vec3(250, 0, zCentroEsfera - 1), 250);
    // Cone* cone2 = new Cone(3, corVermelha, Vec3(200, 0, zCentroEsfera), Vec3(490, 0, zCentroEsfera - 1), 250);
    // Cone* cone3 = new Cone(4, corAzul, Vec3(480, 0, zCentroEsfera), Vec3(730, 0, zCentroEsfera - 1), 250);

    Luz* luzPontual = new Luz(Vec3(0, 60, -30), Vec3(0.7, 0.7, 0.7));

    const int nCol = 500;
    const int nLin = 500;

    const double Dx = (double)wJanela / (double)nCol;
    const double Dy = (double)hJanela / (double)nLin;

    // cenario->objetos.push_back(cilindro);
    cenario->objetos.push_back(esfera);
    cenario->objetos.push_back(chao);
    cenario->objetos.push_back(planoDeFundo);
    // cenario->objetos.push_back(esfera2);
    // cenario->objetos.push_back(cone);
    // cenario->objetos.push_back(cone2);
    // cenario->objetos.push_back(cone3);

    cenario->luzes.push_back(luzPontual);

    cenario->setCanvas(nLin, nCol, Dx, Dy);

    cout << "indo pintar canvas\n";
    cenario->pintarCanvas(dJanela, olhoPintor);

    for (int l = 0; l < nLin; ++l) {
        for (int c = 0; c < nCol; ++c) {
            SDL_Color cor = cenario->canvas->cores[l][c];

            SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
            SDL_RenderDrawPoint(renderer, c, l); // x = coluna que ta e y = linha que ta
        }
    }
    
    cout << "Fim da pintura" << endl;

    SDL_RenderPresent(renderer); // usar no final para pintar

    if ( window = nullptr ) {
        cout << "ERRO:" << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Event windowEvent;
    while (true) {
        if ( SDL_PollEvent(&windowEvent) ) {
            if (SDL_QUIT == windowEvent.type) { break; }
        }
        // else if (windowEvent.type == SDLK_a) { // esquerda
        //     // Um evento de tecla foi pressionado
        //     SDL_Keycode key = windowEvent.key.keysym.sym;
        //     esfera.PCentro.x += 100;

            
            
        //     // Adicione aqui outras ações para teclas específicas
        // }
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}
