#include "../headers/Canvas.h"

using namespace std;

Canvas::Canvas(int hCanvas, int wCanvas, double dX, double dY) : 
    wCanvas(wCanvas), hCanvas(hCanvas), dX(dX), dY(dY) {
    this->cores = new SDL_Color*[hCanvas];
    for (int i = 0; i < hCanvas; ++i) {
        this->cores[i] = new SDL_Color[wCanvas];   
        for (int j = 0; j < wCanvas; ++j) {
            this->cores[i][j] = {100, 100, 100, 255}; // COR PADRAO
        }    
    }
}

void Canvas::pintarTodoCanvas(SDL_Color cor) {
    for (int i = 0; i < hCanvas; ++i) {
        for (int j = 0; j < wCanvas; ++j) {
            this->cores[i][j] = cor;
        }
    }
}

void Canvas::pintarCanvas(int linha, int coluna, SDL_Color cor) {
    this->cores[linha][coluna] = cor;
}

