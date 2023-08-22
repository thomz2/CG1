#include "../headers/Canvas.h"

using namespace std;

Canvas::Canvas(int wCanvas, int hCanvas, double dX, double dY) : wCanvas(wCanvas), hCanvas(hCanvas), dX(dX), dY(dY) {
    this->cores = new SDL_Color*[wCanvas];
    for (int i = 0; i < wCanvas; ++i) {
        this->cores[i] = new SDL_Color[hCanvas];   
        for (int j = 0; j < hCanvas; ++j) {
            this->cores[i][j] = {100, 100, 100, 255}; // COR PADRAO
        }    
    }
}

void Canvas::pintarTodoCanvas(SDL_Color cor) {
    for (int i = 0; i < wCanvas; ++i) {
        for (int j = 0; j < hCanvas; ++j) {
            this->cores[i][j] = cor;
        }
    }
}

void Canvas::pintarCanvas(int x, int y, SDL_Color cor) {
    
    this->cores[x][y] = cor;
}

