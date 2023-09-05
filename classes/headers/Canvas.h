#pragma once
#include <SDL2/SDL.h>
#include <optional>

class Canvas {

    public:
    SDL_Color **cores;
    double dX, dY;
    int nLin, nCol;
    Canvas(int nLin, int nCol, double dX, double dY); 

    void pintarTodoCanvas(SDL_Color cor);
    void pintarCanvas(int linha, int coluna, SDL_Color cor);
    void pintarCanvas(int linha, int coluna, std::optional<SDL_Color> cor);

    // void atualizarCanvas(Scene &cena)
};