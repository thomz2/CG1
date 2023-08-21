#include <iostream>
#include <SDL2/SDL.h>
#include "classes/headers/vec3.h"

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

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
    SDL_RenderDrawPoint(renderer, 45, 59);
    SDL_RenderClear(renderer);
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
