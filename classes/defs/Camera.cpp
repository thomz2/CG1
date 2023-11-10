#include "./../headers/Camera.h"
#include <math.h>
#define M_PI 3.14159265358979323846

using namespace std;

double degreesToRadian(double dgvalue) {
    return dgvalue * (M_PI/180);
}

Camera::Camera(Vec3 olhoPintor, Vec3 centroJanela, double dJanela, double vFov, double imageWidth, double imageHeight, double kFov) {
    this->initialize(olhoPintor, centroJanela, dJanela, vFov, imageWidth, imageHeight, kFov);
}

// construtor mais simples sem fov
Camera::Camera(Vec3 olhoPintor, Vec3 centroJanela, double dJanela, double wJanela, double hJanela) 
 : olhoPintor(olhoPintor), centroJanela(centroJanela), dJanela(dJanela), wJanela(wJanela), hJanela(hJanela) {}

void Camera::initialize(Vec3 olhoPintor, Vec3 centroJanela, double dJanela, double vFov, double imageWidth, double imageHeight, double kFov) {

    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;

    this->olhoPintor = olhoPintor;
    this->centroJanela = centroJanela;
    this->dJanela = dJanela;
    this->vFov = vFov;
    this->theta = degreesToRadian(vFov);
    this->h = tan(theta/2);

    this->hJanela = 2 * h * kFov;
    this->wJanela = hJanela * (imageWidth/imageHeight);

    cout << "[ H, W ] = " << hJanela << " " << wJanela << endl;

}

void Camera::changeFog(double vFov) {

    if (imageWidth < 0 || imageHeight < 0) return;

    this->vFov = vFov;
    this->theta = degreesToRadian(vFov);
    this->h = tan(theta/2);

    this->hJanela = 2 * h;
    this->wJanela = hJanela * (imageWidth/imageHeight);
}