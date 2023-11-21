#include "../headers/Canvas.h"
#include <optional>
#include <iostream>

using namespace std;

Canvas::Canvas(int nLin, int nCol, double dX, double dY) : 
    nCol(nCol), nLin(nLin), dX(dX), dY(dY) {
    this->cores = new SDL_Color*[nLin];
    for (int i = 0; i < nLin; ++i) {
        this->cores[i] = new SDL_Color[nCol];   
        for (int j = 0; j < nCol; ++j) {
            this->cores[i][j] = {100, 100, 100, 255}; // COR PADRAO
        }    
    }
}

void Canvas::pintarTodoCanvas(SDL_Color cor) {
    for (int i = 0; i < nLin; ++i) {
        for (int j = 0; j < nCol; ++j) {
            this->cores[i][j] = cor;
        }
    }
}

void Canvas::pintarCanvas(int linha, int coluna, SDL_Color cor) {
        // cout << "POSICAO NULA: " << linha << ", " << coluna << endl;
    // if (this->cores != nullptr && this->cores[linha] != nullptr)
        this->cores[linha][coluna] = cor;
 
}

void Canvas::pintarCanvas(int linha, int coluna, optional<SDL_Color> cor) {
    
    if (cor.has_value()) { 
        this->cores[linha][coluna] = cor.value();
    } else {
        this->cores[linha][coluna] = {100, 100, 100, 255}; // COR PADRAO
    }
}


