#include <iostream>
#include <SDL2/SDL.h>
#include "classes/headers/Vec3.h"
#include "classes/headers/Canvas.h"
#include "classes/headers/Esfera.h"
#include "classes/headers/Ray.h"

using namespace std;

const int wJanela = 800, hJanela = 600;

void initializeSDLAndWindow (
    SDL_Window** window,
    SDL_Renderer** renderer,
    int width,
    int height
) {
    SDL_Init (SDL_INIT_EVERYTHING);

    // SDL_CreateWindowAndRenderer (
    //     800*4, 600*4, 0, &window, &renderer
    // );
    // SDL_RenderSetScale(renderer, 4, 4);

    SDL_CreateWindowAndRenderer (
        width, height, 0, window, renderer
    );
}

int main ( int argc, char *argv[] ) {

    SDL_Window *window; // = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wJanela, hJanela, SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_Renderer *renderer;

    initializeSDLAndWindow(&window, &renderer, wJanela, hJanela);

    const double dJanela = 1000;
    const double rEsfera = 20;
    const double zCentroEsfera = - (dJanela + rEsfera) - 600; // sempre diminuindo um valor

    Vec3 centroJanela(0, 0, -dJanela);
    Vec3 olhoPintor(0, 0, 0);

    SDL_Color corEsfera = {255, 0, 0, 255};

    Esfera esfera(Vec3(0, 0, zCentroEsfera), rEsfera);

    const double nCol = wJanela / 1;
    const double nLin = hJanela / 1;

    const double Dx = wJanela / nCol;
    const double Dy = hJanela / nLin;

    Canvas meuCanvas(wJanela, hJanela, 1, 1);

    for (int l = 0; l < nLin; ++l) {
        
        // double y = hJanela/2 - Dy/2 - l*Dy;
        int y = l;
        
        for (int c = 0; c < nCol; ++c) {

            // double x = -wJanela/2 + Dx/2 + c*Dx;
            int x = c;

            Vec3 PosJanela(x, y, -dJanela);
            Vec3 direcao = (PosJanela - olhoPintor).norm();
            Ray raycaster(olhoPintor, direcao);

            // cor[x][y] <- raycasting(raio, cenario)
            if (esfera.intersecta(raycaster)) {
                meuCanvas.pintarCanvas(x, y, corEsfera);

                // cout << "POS ESFERA: " << x << " " << y << endl;

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
            } else {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 1);
            }

                SDL_RenderDrawPoint(renderer, (int)x, (int)y);


            // Dx * Dy pixels para pintar
            // for (int xi = 0; xi < Dx; ++xi) {
            //     for (int yj = 0; yj < Dy; ++yj) {
                    
            //     }
            // }

        }
    }

    for (int x = 0; x < 800; x++) {
        for (int y = 0; y < 600; y++) {
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    // usar no loop
    // const double x = - wJanela/2 + Dx/2  + c*Dx;
    // const double y =   hJanela/2 - Dy/2  - l*Dy;


    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
    // SDL_RenderDrawPoint(renderer, 45, 59);
    // SDL_RenderClear(renderer);
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
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}
