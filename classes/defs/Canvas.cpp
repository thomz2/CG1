#include "../headers/Canvas.h"

using namespace std;

Canvas::Canvas(int wJanela, int hJanela) {
    this->cores = new SDL_Color*[wJanela];
    for (int i = 0; i < wJanela; ++i) {
        this->cores[i] = new SDL_Color[hJanela];   
        for (int j = 0; j < hJanela; ++j) {
            this->cores[i][j] = {100, 100, 100, 255}; // COR PADRAO
        }    
    }
}

void Canvas::PintarCanvas(SDL_Color cor) {
    for (int i = 0; i < wJanela; ++i) {
        for (int j = 0; j < hJanela; ++j) {
            this->cores[i][j] = cor;
        }
    }
}