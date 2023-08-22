#include <SDL2/SDL.h>

class Canvas {
    private:
    int wJanela, hJanela;

    public:
    SDL_Color **cores;
    Canvas(int wJanela, int hJanela); 

    void PintarCanvas(SDL_Color cor);
};