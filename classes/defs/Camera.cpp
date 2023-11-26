// ISSO EH A CAMERA PERSPECTIVA

#include "./../headers/Camera.h"
#include "./../headers/Ray.h"
#include "./../headers/Scene.h"

#include <math.h>
#include <cstdlib>
#define M_PI 3.14159265358979323846

using namespace std;

double degreesToRadian(double dgvalue) {
    return dgvalue * (M_PI/180);
}

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

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
    cout << "NOVOS VALORES: HJANELA: " << hJanela << ", WJANELA: " << wJanela << ", DFOCAL: " << focal_length << endl;


    // // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    // this->w = lookfrom.sub(lookat).norm();
    // this->u = vup.cross(w);
    // this->v = w.cross(u);

    // // informacoes de renderizacao
    // viewport_u = u.mult(wJanela);
    // viewport_v = v.mult(-hJanela);

    // pixel_delta_u = viewport_u.div(imageWidth);
    // pixel_delta_v = viewport_v.div(imageHeight);

    // viewport_upper_left 
    //     = center.sub((w.mult(focal_length))).sub(viewport_u.div(2)).sub(viewport_v.div(2));

    // pixel00_loc = viewport_upper_left.add( (pixel_delta_u.add(pixel_delta_v)).mult(0.5) );

    update();

}

void Camera::update() {
    if (imageWidth < 0 || imageHeight < 0) return;

    Vec3 center = lookfrom;

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

    lookfrom_upper_left
        = center.sub(viewport_u.div(2)).sub(viewport_v.div(2));


    pixel00_loc = viewport_upper_left.add( (pixel_delta_u.add(pixel_delta_v)).mult(0.5) );
    pixel00_loc2 = lookfrom_upper_left.add( (pixel_delta_u.add(pixel_delta_v)).mult(0.5) );
}

void Camera::initializeRenderAndWindow(int width, int height, SDL_Renderer **renderer, SDL_Window **window) {
    SDL_Init (SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer (
        width, height, 0, window, renderer
    );
}

SDL_Color Camera::renderPixel(int l, int c) {
    Vec3 pixel_center = pixel00_loc.add(pixel_delta_u.mult(c)).add(pixel_delta_v.mult(l));
    Vec3 direcao = (pixel_center - lookfrom).norm(); // vetor unitario aki
    Ray raycaster(lookfrom, direcao);
    if (isParalel) {
        // cout << "oi";
        pixel_center = pixel00_loc2.add(pixel_delta_u.mult(c)).add(pixel_delta_v.mult(l));
        direcao = (lookat - lookfrom).norm();
        raycaster = Ray(pixel_center, direcao);
    }

    // TODO: refatorar funcao firstObj dps
    optional<pair<Objeto*, LPointGetType>> par = cenario->firstObj2(raycaster);

    if (par.has_value()) {
        Objeto* maisPerto = par.value().first;
        LPointGetType retorno = par.value().second;

        // foi intersectado
        if (maisPerto != nullptr) {
            
            Vec3 ponto_mais_prox = retorno.posContato;
            Vec3 normal          = retorno.normalContato.norm();
            double tint          = retorno.tint;

            BaseMaterial material = maisPerto->material;
            // cout << retorno.material.value().KAMBIENTE << " PROVANDO QUE TEM\n";
            if (retorno.material.has_value()) {
                material = retorno.material.value();
            }

            Vec3 intensidadeCor = material.getKAmbiente() | cenario->luzAmbiente;

            for (Luz* luz: cenario->luzes) {
                intensidadeCor = intensidadeCor.add(luz->calcIntensity(cenario->objetos, retorno, raycaster, material));

                if (intensidadeCor.x > 1) intensidadeCor.x = 1;
                if (intensidadeCor.y > 1) intensidadeCor.y = 1;
                if (intensidadeCor.z > 1) intensidadeCor.z = 1;
            }

            Vec3 corNova = intensidadeCor * 255;

            SDL_Color corNovaPintar = {
                (Uint8)corNova.x,
                (Uint8)corNova.y,
                (Uint8)corNova.z,
                255 // ver isso dps
            };

            return corNovaPintar;

        }
    }

    return {100, 100, 100, 255};

}

void Camera::renderAndPaintCanvas(int resScale) {
    // cenario->canvas->pintarTodoCanvas({100, 100, 100, 255});

    for (int l = 0; l < cenario->canvas->nLin; l += resScale) {
        for (int c = 0; c < cenario->canvas->nCol; c += resScale) {
            SDL_Color corNovaPintar = this->renderPixel(l, c);
            for (int i = 0; i < resScale; ++i) {
                for (int j = 0; j < resScale; j++) {
                    cenario->canvas->pintarCanvas(l + i, c + j, corNovaPintar);
                }
            }
        }
    }
}

void Camera::renderAndPaintCanvasThread(int numThreads, int resScale) {
    // Vetor para armazenar threads
    std::vector<std::thread> threads;

    // Função para renderizar um quadrante
    auto renderQuadrante = [this, resScale](int lStart, int lEnd, int cStart, int cEnd) {
        for (int l = lStart; l < lEnd; l += resScale) {
            for (int c = cStart; c < cEnd; c += resScale) {
                SDL_Color corNovaPintar = this->renderPixel(l, c);
                for (int i = 0; i < resScale; ++i) {
                    for (int j = 0; j < resScale; j++) {
                        if (l + i < cenario->canvas->nLin && c + j < cenario->canvas->nCol){
                            // if (l+i > 450) cout << l + i << " " << c + j << endl;
                            cenario->canvas->pintarCanvas(l + i, c + j, corNovaPintar);
                        }
                    }
                }
            }
        }
    };

    // Calcula as dimensões dos quadrantes
    int quadWidth = cenario->canvas->nCol / numThreads;
    int quadHeight = cenario->canvas->nLin / numThreads;

    // Cria threads para renderizar quadrantes
    for (int i = 0; i < numThreads; ++i) {
        int lStart = i * quadHeight;
        int lEnd = (i + 1) * quadHeight;
        if (lEnd >= cenario->canvas->nLin) lEnd = cenario->canvas->nLin - 1;
        for (int j = 0; j < numThreads; ++j) {
            int cStart = j * quadWidth;
            int cEnd = (j + 1) * quadWidth;
            if (cEnd >= cenario->canvas->nCol) cEnd = cenario->canvas->nCol - 1;

            threads.emplace_back(renderQuadrante, lStart, lEnd, cStart, cEnd);
        }
    }

    // Aguarda todas as threads terminarem
    for (auto& thread : threads) {
        thread.join();
    }
}

void Camera::changeFov(double vFov) {

    if (imageWidth < 0 || imageHeight < 0) return;

    this->vFov = vFov;
    this->theta = degreesToRadian(vFov);
    this->h = tan(theta/2);

    this->hJanela = 2 * h * focal_length;
    this->wJanela = hJanela * (imageWidth/imageHeight);

    update();

    cout << "NOVOS VALORES: HJANELA: " << hJanela << ", WJANELA: " << wJanela << ", DFOCAL: " << focal_length << endl;

}

void Camera::changeFovAlt(double dFocal, double wJanela, double hJanela) {

    this->focal_length = dFocal;
    this->hJanela = hJanela;
    this->wJanela = wJanela;

    update();

    cout << "NOVOS VALORES: HJANELA: " << hJanela << ", WJANELA: " << wJanela << ", DFOCAL: " << focal_length << endl;

}

void Camera::changeCamera() {
    this->isParalel = !(this->isParalel);
}