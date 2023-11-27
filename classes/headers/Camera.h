#pragma once
#include "./math/Vec3.h"
#include <SDL2/SDL.h>
#include <optional>
#include "./primitives/Objeto.h"
#include "./types/LPointGetType.h"
#include "./Scene.h"
#include "./luzes/Luz.h"
#include <thread>
#include <vector>

class Scene;

class Camera {
    public:

        Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vFov, double imageWidth, double imageHeight);

        void initialize2(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vFov, double imageWidth, double imageHeight);
        void update();
        void initializeRenderAndWindow(int width, int height, SDL_Renderer **renderer, SDL_Window **window);
        SDL_Color renderPixel(int l, int c);
        void renderAndPaintCanvas(int resScale = 1);
        void renderAndPaintCanvasThread(int numThreads, int resScale = 1);
        void changeFov(double vFov);
        void changeFovAlt(double dFocal, double wJanela, double hJanela);
        void changeCamera();

        // controles
        void moveForward(float speed);
        void moveBackward(float speed);
        void moveLeft(float speed);
        void moveRight(float speed);
        void moveDown(float speed);
        void moveUp(float speed);


        Scene* cenario;
        bool isParalel = false;

        // verificar se esses valores sao -1, se forem, eh pq nao sao utilizados (usamos tamanhos de janela predefinidos)
        double vFov = -1;
        double theta = -1;
        double h = -1;
        double imageWidth = -1;
        double imageHeight = -1;

        double hJanela;
        double wJanela;
        double focal_length;

        // Positioning and Orienting the Camera
        Vec3 lookfrom = Vec3(0,0,-1);  // Point camera is looking from
        Vec3 lookat   = Vec3(0,0,0);   // Point camera is looking at
        Vec3 vup      = Vec3(0,1,0);   // Camera-relative "up" direction

        Vec3 u, v, w; // Camera frame basis vectors

        // informacoes de renderizacao
        Vec3 viewport_u;
        Vec3 viewport_v;

        Vec3 pixel_delta_u;
        Vec3 pixel_delta_v;

        Vec3 viewport_upper_left;
        Vec3 pixel00_loc;

        Vec3 lookfrom_upper_left;
        Vec3 pixel00_loc2;

};