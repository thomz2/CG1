#pragma once
#include "./math/Vec3.h"

class Camera {
    public:

        Camera(Vec3 olhoPintor, Vec3 centroJanela, double dJanela, double vFov, double imageWidth, double imageHeight, double kFov);
        Camera(Vec3 olhoPintor, Vec3 centroJanela, double dJanela, double wJanela, double hJanela);
        void initialize(Vec3 olhoPintor, Vec3 centroJanela, double dJanela, double vFov, double imageWidth, double imageHeight, double kFov);
        void changeFog(double vFov);

        // verificar se esses valores sao -1, se forem, eh pq nao sao utilizados (usamos tamanhos de janela predefinidos)
        double vFov = -1;
        double theta = -1;
        double h = -1;
        double imageWidth = -1;
        double imageHeight = -1;

        double hJanela;
        double wJanela;
        double dJanela;

        Vec3 centroJanela;
        Vec3 olhoPintor;
};