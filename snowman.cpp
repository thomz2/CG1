// TODO: implementar destrutores nas classes

#include <iostream>
#include <SDL.h>
#include "classes/headers/math/Vec3.h"
#include "classes/headers/primitives/Esfera.h"
#include "classes/headers/Canvas.h"
#include "classes/headers/Ray.h"
#include "classes/headers/Scene.h"
#include "classes/headers/primitives/Cilindro.h"

using namespace std;

const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

int m5 ( int argc, char *argv[] ) {

    SDL_Window *window;
    SDL_Renderer *renderer = nullptr;

    const int wJanela = 1600 * 1;
    const int hJanela = 1200 * 1;

    // initializeSDLAndWindow(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    const double dJanela = 50000;
    const double rEsfera = 150;
    const double zCentroEsfera = - (dJanela + rEsfera) - 50; // sempre diminuindo um valor

    Vec3 centroJanela(0, 0, -dJanela);
    Vec3 olhoPintor(0, 0, 0);

    SDL_Color corEsferaBranca = {255, 255, 255, 255};
    SDL_Color corEsferaPreto = {0, 0, 0, 255};
    SDL_Color corEsferaLaranja = {255, 165, 0, 255};
    SDL_Color corEsferaVermelhoEscuro = {139, 0, 0, 255};
    SDL_Color corEsferaVermelhoClaro = {255, 105, 97, 255};

    Esfera* esfera = new Esfera(0, corEsferaBranca, Vec3(0, -100, zCentroEsfera), rEsfera);
    Esfera* esfera2 = new Esfera(1, corEsferaBranca, Vec3(0, 150, zCentroEsfera), rEsfera - 35);

    Esfera* botoes[] = {
        new Esfera(2, corEsferaVermelhoEscuro, Vec3(0, -25, zCentroEsfera +150), 17),
        new Esfera(3, corEsferaVermelhoEscuro, Vec3(0, -100, zCentroEsfera +150), 17),
        new Esfera(4, corEsferaVermelhoEscuro, Vec3(0, -175, zCentroEsfera +150), 17)
    };

    Esfera* nariz = new Esfera(5, corEsferaLaranja, Vec3(0, 150, zCentroEsfera +151), 15);

    Esfera* olhos[] = {
        new Esfera(6, corEsferaPreto, Vec3(-50, 200, zCentroEsfera +50), 15),
        new Esfera(7, corEsferaPreto, Vec3(50, 200, zCentroEsfera +50), 15)
    };

    Esfera* brilhos[] = {
        new Esfera(8, corEsferaBranca, Vec3(-55, 207, zCentroEsfera +55), 5),
        new Esfera(9, corEsferaBranca, Vec3(45, 207, zCentroEsfera +55), 5)
    };

    Esfera* boca[] = {
        new Esfera(10, corEsferaPreto, Vec3(-60, 110, zCentroEsfera +50), 13),
        new Esfera(11, corEsferaPreto, Vec3(-30, 100, zCentroEsfera +50), 13),
        new Esfera(12, corEsferaPreto, Vec3(0, 95, zCentroEsfera +50), 13),
        new Esfera(13, corEsferaPreto, Vec3(30, 100, zCentroEsfera +50), 13),
        new Esfera(14, corEsferaPreto, Vec3(60, 110, zCentroEsfera +50), 13)
    };

    Esfera* bochechas[] = {
        new Esfera(15, corEsferaVermelhoClaro, Vec3(-50, 150, zCentroEsfera +50), 13),
        new Esfera(16, corEsferaVermelhoClaro, Vec3(50, 150, zCentroEsfera +50), 13)
    };

    Cilindro* chapeu[] = {
        new Cilindro(17, corEsferaPreto, Vec3(0, 350, zCentroEsfera), Vec3(0, 400, zCentroEsfera), 105),
        new Cilindro(18, corEsferaPreto, Vec3(0, 280, zCentroEsfera), Vec3(0, 310, zCentroEsfera), 165)
    };

    Cilindro* bracos[] = {
        new Cilindro(19, corEsferaLaranja, Vec3(-240, 0, zCentroEsfera - 1350), Vec3(-400, 50, zCentroEsfera - 1350), 10),
        new Cilindro(20, corEsferaLaranja, Vec3(240, 0, zCentroEsfera), Vec3(400, 50, zCentroEsfera), 10)
    };

    const int nCol = 800;
    const int nLin = 600;

    const double Dx = (double)wJanela / (double)nCol;
    const double Dy = (double)hJanela / (double)nLin;

    cenario->objetos.push_back(esfera);
    cenario->objetos.push_back(esfera2);

    for (int i = 0; i < 3; ++i) {
        cenario->objetos.push_back(botoes[i]);
    }

    cenario->objetos.push_back(nariz);

    for (int i = 0; i < 2; ++i) {
        cenario->objetos.push_back(olhos[i]);
        cenario->objetos.push_back(brilhos[i]);
        cenario->objetos.push_back(bochechas[i]);
        cenario->objetos.push_back(chapeu[i]);
        cenario->objetos.push_back(bracos[i]);
    }

    for (int i = 0; i < 5; ++i) {
        cenario->objetos.push_back(boca[i]);
    }

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
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}
