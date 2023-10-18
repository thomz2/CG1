// TODO: implementar destrutores nas classes

#include <iostream>
#include <SDL2/SDL.h>
#include "classes/headers/math/Vec3.h"
#include "classes/headers/primitives/Plano.h"
#include "classes/headers/primitives/Circulo.h"
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

    SDL_Color corBranco = {255, 255, 255, 255};
    SDL_Color corVermelha = {255, 0, 0, 255};
    SDL_Color corVerde = {0, 255, 0, 255};
    SDL_Color corVerdeEscuro = {0, 60, 0, 255};
    SDL_Color corAzul = {0, 0, 255, 255};
    SDL_Color corBiscoito = {224, 179, 134, 255};
    SDL_Color corChocolate = {128, 90, 70, 255};
    SDL_Color corAzulMeleca = {128, 152, 182, 255};
    SDL_Color corMarromPiso = {128, 64, 0, 255};

    Luz* luzTeste = new Luz(Vec3(-2000, 3000, 100), Vec3(1, 1, 1));
    Luz* luzTeste2 = new Luz(Vec3(100, -4000, 100), Vec3(2, 2, 2));

    Plano* parede = new Plano(10, corAzulMeleca, MaterialTarefa(), Vec3(0,0,zCentroEsfera - 3300), Vec3(0,0,1));
    Plano* piso = new Plano(11, corBranco, MaterialTarefa(), Vec3(0, -400, 0), Vec3(0,1,0));

    Cilindro* pesmesa[] = {
        new Cilindro(1, corChocolate, Vec3(-600, -400, zCentroEsfera + 450), Vec3(-600, -200, zCentroEsfera + 450), 20, MaterialTarefa()),
        // -1 1
        new Cilindro(2, corChocolate, Vec3(-100, -400, zCentroEsfera + 450), Vec3(-100, -200, zCentroEsfera + 450), 20, MaterialTarefa()),
        // 1 1
        new Cilindro(3, corChocolate, Vec3(-600, -400, zCentroEsfera - 50), Vec3(-600, -200, zCentroEsfera - 50), 20, MaterialTarefa()),
        // -1 -1
        new Cilindro(4, corChocolate, Vec3(-100, -400, zCentroEsfera - 50), Vec3(-100, -200, zCentroEsfera - 50), 20, MaterialTarefa())
        // 1 -1
    };
    // mudar esse abaixo para cilindro
    // Circulo* baseMesa = new Circulo(5, corChocolate, BaseMaterial(), Vec3(-350, -200, zCentroEsfera + 200), Vec3(0,1,0), 400);
    Cilindro* baseMesa = new Cilindro(5, corChocolate, Vec3(-350, -200, zCentroEsfera + 200), Vec3(-350, -100, zCentroEsfera + 200), 400);
    
    Cilindro* tronco = new Cilindro(6, corMarromPiso, Vec3(500, -400, zCentroEsfera + 200), Vec3(500, -100, zCentroEsfera + 200), 60);
    Cone* folhas[] = {
        new Cone(7, corVerdeEscuro, Vec3(500, -100, zCentroEsfera + 200), Vec3(500, 200, zCentroEsfera + 200), 290),
        new Cone(8, corVerdeEscuro, Vec3(500, 100, zCentroEsfera + 200), Vec3(500, 400, zCentroEsfera + 200), 250),
        new Cone(9, corVerdeEscuro, Vec3(500, 300, zCentroEsfera + 200), Vec3(500, 600, zCentroEsfera + 200), 210),
    };

    // Esfera* bola = new Esfera(1, corVerde, Vec3(0, 0, zCentroEsfera - 300), 300, MaterialTarefa());
    // Cone* cone = new Cone(2, corVermelha, Vec3(0, -100, zCentroEsfera), Vec3(0, 100, zCentroEsfera), 250, MaterialTarefa());

    // BONECO DE NEVE

    const double rEsferaSnowMan        = 150;
    const double constanteDeIrPDireita = 120;  // pro x
    const double constanteDeIrPBaixo   = -150; // pro y
    const double constanteDeIrPtras    = -300; // pro z (adicionar ao zCentroEsfera)

    SDL_Color corEsferaBranca = {255, 255, 255, 255};
    SDL_Color corEsferaPreto = {0, 0, 0, 255};
    SDL_Color corEsferaLaranja = {255, 165, 0, 255};
    SDL_Color corEsferaVermelhoEscuro = {139, 0, 0, 255};
    SDL_Color corEsferaVermelhoClaro = {255, 105, 97, 255};

    Esfera* esfera = new Esfera(0, corEsferaBranca, Vec3(0 + constanteDeIrPDireita, -100 + constanteDeIrPBaixo, zCentroEsfera), rEsferaSnowMan);
    Esfera* esfera2 = new Esfera(1, corEsferaBranca, Vec3(0 + constanteDeIrPDireita, 150 + constanteDeIrPBaixo, zCentroEsfera), rEsferaSnowMan - 35);

    Esfera* botoes[] = {
        new Esfera(2, corEsferaVermelhoEscuro, Vec3(0 + constanteDeIrPDireita, -25 + constanteDeIrPBaixo, zCentroEsfera +125), 17),
        new Esfera(3, corEsferaVermelhoEscuro, Vec3(0 + constanteDeIrPDireita, -100 + constanteDeIrPBaixo, zCentroEsfera +140), 17),
        new Esfera(4, corEsferaVermelhoEscuro, Vec3(0 + constanteDeIrPDireita, -175 + constanteDeIrPBaixo, zCentroEsfera +125), 17)
    };

    // Esfera* nariz = new Esfera(5, corEsferaLaranja, Vec3(0 + constanteDeIrPDireita, 150 + constanteDeIrPBaixo, zCentroEsfera +135), 15);
    Cone* nariz = new Cone(5, corEsferaLaranja, Vec3(0 + constanteDeIrPDireita, 150 + constanteDeIrPBaixo, zCentroEsfera +110), Vec3(0 + constanteDeIrPDireita, 150 + constanteDeIrPBaixo, zCentroEsfera +160), 15);

    Esfera* olhos[] = {
        new Esfera(6, corEsferaPreto, Vec3(-50 + constanteDeIrPDireita, 200 + constanteDeIrPBaixo, zCentroEsfera +100), 15),
        new Esfera(7, corEsferaPreto, Vec3(50 + constanteDeIrPDireita, 200 + constanteDeIrPBaixo, zCentroEsfera +100), 15)
    };

    Esfera* boca[] = {
        new Esfera(10, corEsferaPreto, Vec3(-60 + constanteDeIrPDireita, 110 + constanteDeIrPBaixo, zCentroEsfera +100), 13),
        new Esfera(11, corEsferaPreto, Vec3(-30 + constanteDeIrPDireita, 100 + constanteDeIrPBaixo, zCentroEsfera +100), 13),
        new Esfera(12, corEsferaPreto, Vec3(0 + constanteDeIrPDireita, 95 + constanteDeIrPBaixo, zCentroEsfera +100), 13),
        new Esfera(13, corEsferaPreto, Vec3(30 + constanteDeIrPDireita, 100 + constanteDeIrPBaixo, zCentroEsfera +100), 13),
        new Esfera(14, corEsferaPreto, Vec3(60 + constanteDeIrPDireita, 110 + constanteDeIrPBaixo, zCentroEsfera +100), 13)
    };

    Esfera* bochechas[] = {
        new Esfera(15, corEsferaVermelhoClaro, Vec3(-50 + constanteDeIrPDireita, 150 + constanteDeIrPBaixo, zCentroEsfera +50), 13),
        new Esfera(16, corEsferaVermelhoClaro, Vec3(50 + constanteDeIrPDireita, 150 + constanteDeIrPBaixo, zCentroEsfera +50), 13)
    };

    Cilindro* chapeu[] = {
        new Cilindro(17, corEsferaPreto, Vec3(0 + constanteDeIrPDireita, 290 + constanteDeIrPBaixo, zCentroEsfera), Vec3(0 + constanteDeIrPDireita, 400 + constanteDeIrPBaixo, zCentroEsfera), 105),
        new Cilindro(18, corEsferaPreto, Vec3(0 + constanteDeIrPDireita, 240 + constanteDeIrPBaixo, zCentroEsfera), Vec3(0 + constanteDeIrPDireita, 290 + constanteDeIrPBaixo, zCentroEsfera), 165)
    };

    const int nCol = 800;
    const int nLin = 600;

    const int Dx = wJanela / nCol;
    const int Dy = hJanela / nLin;

    cenario->objetos.push_back(parede);
    cenario->objetos.push_back(piso);
    // cenario->objetos.push_back(bola);
    // cenario->objetos.push_back(cone);
    // cenario->objetos.push_back(cilindro);

    for (int i = 0; i < 4; ++i) {
        cenario->objetos.push_back(pesmesa[i]);
    }
    cenario->objetos.push_back(baseMesa);

    cenario->objetos.push_back(tronco);
    for (int i = 0; i < 3; ++i) {
        cenario->objetos.push_back(folhas[i]);
    }

    cenario->objetos.push_back(esfera);
    cenario->objetos.push_back(esfera2);

    for (int i = 0; i < 3; ++i) {
        cenario->objetos.push_back(botoes[i]);
    }

    cenario->objetos.push_back(nariz);

    for (int i = 0; i < 2; ++i) {
        cenario->objetos.push_back(olhos[i]);
        // cenario->objetos.push_back(brilhos[i]);
        cenario->objetos.push_back(bochechas[i]);
        cenario->objetos.push_back(chapeu[i]);
        // cenario->objetos.push_back(bracos[i]);
    }

    for (int i = 0; i < 5; ++i) {
        cenario->objetos.push_back(boca[i]);
    }

    cenario->luzes.push_back(luzTeste);
    // cenario->luzes.push_back(luzTeste2);

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
