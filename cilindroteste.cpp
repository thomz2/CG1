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

const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

// void initializeSDLAndWindow (
//     SDL_Window** window,
//     SDL_Renderer** renderer,
//     int width,
//     int height
// ) {
//     SDL_Init (SDL_INIT_EVERYTHING);

//     // SDL_CreateWindowAndRenderer (
//     //     800*4, 600*4, 0, &window, &renderer
//     // );
//     // SDL_RenderSetScale(renderer, 4, 4);

//     SDL_CreateWindowAndRenderer (
//         width, height, 0, window, renderer
//     );
// }

int main ( int argc, char *argv[] ) {

    SDL_Window *window; // = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wJanela, hJanela, SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_Renderer *renderer;

    const int wJanela = 1600, hJanela = 1200;

    // initializeSDLAndWindow(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    const double dJanela = 4000;
    const double rEsfera = 100;
    const double zCentroEsfera = - (dJanela + rEsfera) - 250; // sempre diminuindo um valor

    Vec3 centroJanela(0, 0, -dJanela);
    Vec3 olhoPintor(0, 0, 0);

    SDL_Color corVermelha = {255, 0, 0, 255};
    SDL_Color corVerde = {0, 255, 0, 255};
    SDL_Color corAzul = {0, 0, 255, 255};
    SDL_Color corBiscoito = {224, 179, 134, 255};
    SDL_Color corChocolate = {128, 90, 70, 255};

    Luz* luzTeste = new Luz(Vec3(-100, 2000, -100), Vec3(1, 1, 1));
    Luz* luzTeste2 = new Luz(Vec3(100, -2000, 100), Vec3(2, 2, 2));

    Esfera* bola = new Esfera(1, corVerde, Vec3(0, 0, zCentroEsfera - 300), 300, MaterialTarefa());
    Cone* cone = new Cone(2, corVermelha, Vec3(0, 0, zCentroEsfera), Vec3(200, -200, zCentroEsfera - 200), 150, MaterialTarefa());
    Cilindro* cilindro = new Cilindro(3, corAzul, Vec3(0, 0, zCentroEsfera), Vec3(200, -200, zCentroEsfera - 200), 150, MaterialTarefa());


    const int nCol = 800;
    const int nLin = 600;

    const double Dx = (double)wJanela / (double)nCol;
    const double Dy = (double)hJanela / (double)nLin;

    // cenario->objetos.push_back(bola);
    cenario->objetos.push_back(cone);
    // cenario->objetos.push_back(cilindro);

    // cenario->luzes.push_back(luzTeste);
    cenario->luzes.push_back(luzTeste2);

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
