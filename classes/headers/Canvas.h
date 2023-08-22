#include <SDL2/SDL.h>

class Canvas {
    private:
    int wCanvas, hCanvas;

    public:
    SDL_Color **cores;
    double dX, dY;
    Canvas(int wCanvas, int hCanvas, double dX, double dY); 

    void pintarTodoCanvas(SDL_Color cor);
    void pintarCanvas(int x, int y, SDL_Color cor);

};