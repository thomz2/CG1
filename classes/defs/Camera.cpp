#include "./../headers/Camera.h"
#include <math.h>
#define M_PI 3.14159265358979323846

using namespace std;

double degreesToRadian(double dgvalue) {
    return dgvalue * (M_PI/180);
}

// DEPRECADO KK
Camera::Camera(Vec3 lookfrom, Vec3 lookat, double focal_length, double vFov, double imageWidth, double imageHeight, double kFov) {
    this->initialize(lookfrom, lookat, focal_length, vFov, imageWidth, imageHeight, kFov);
}

// construtor mais simples sem fov
// DEPRECADO KK
Camera::Camera(Vec3 lookfrom, Vec3 lookat, double focal_length, double wJanela, double hJanela) 
 : lookfrom(lookfrom), lookat(lookat), focal_length(focal_length), wJanela(wJanela), hJanela(hJanela) {}

Camera::Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vFov, double imageWidth, double imageHeight) 
 : lookfrom(lookfrom), lookat(lookat), vup(vup), vFov(vFov), imageWidth(imageWidth), imageHeight(imageHeight) {
    this->initialize2(lookfrom, lookat, vup, vFov, imageWidth, imageHeight);
}

void Camera::initialize2(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vFov, double imageWidth, double imageHeight) {

    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;

    Vec3 center = lookfrom;

    this->focal_length = (lookfrom.sub(lookat)).modulo();
    this->theta = degreesToRadian(vFov);
    this->h = tan(theta/2);
    this->hJanela = 2 * h * focal_length;
    this->wJanela = hJanela * (imageWidth/imageHeight);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    this->w = lookfrom.sub(lookat).norm();
    this->u = vup.cross(w);
    this->v = w.cross(u);

    // informacoes de renderizacao
    viewport_u = u.mult(wJanela);
    viewport_v = v.mult(-hJanela);

    pixel_delta_u = viewport_u.div(imageWidth);
    pixel_delta_v = viewport_v.div(imageHeight);

    viewport_upper_left 
        = center.sub((w.mult(focal_length))).sub(viewport_u.div(2)).sub(viewport_v.div(2));

    pixel00_loc = viewport_upper_left.add( (pixel_delta_u.add(pixel_delta_v)).mult(0.5) );


}

// DEPRECADO KK
void Camera::initialize(Vec3 lookfrom, Vec3 lookat, double focal_length, double vFov, double imageWidth, double imageHeight, double kFov) {

    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;

    this->lookfrom = lookfrom; // eh o CENTRO
    this->lookat = lookat;
    this->focal_length = focal_length;
    this->vFov = vFov;
    this->theta = degreesToRadian(vFov);
    this->h = tan(theta/2);

    this->hJanela = 2 * h * kFov;
    this->wJanela = hJanela * (imageWidth/imageHeight);

    cout << "[ H, W ] = " << hJanela << " " << wJanela << endl;

}

void Camera::changeFov(double vFov) {

    if (imageWidth < 0 || imageHeight < 0) return;

    this->vFov = vFov;
    this->theta = degreesToRadian(vFov);
    this->h = tan(theta/2);

    this->hJanela = 2 * h;
    this->wJanela = hJanela * (imageWidth/imageHeight);
}