#include "../../../headers/primitives/mesh/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../headers/stb/stb_image.h"
#include <iostream>

using namespace std;

Texture::Texture() {}
Texture::Texture(const char* filePath) {
    readFromFilePath(filePath);
}

bool Texture::readFromFilePath(const char* filePath) {
    int width, height, channels;
    unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

    if (data) {

        cout << "entrou no if data" << endl;

        this->w = width;
        this->h = height;
        this->initializeMatrix(width, height);

        // Assuming the texture has 3 channels (RGB)
        for (int y = 0; y < height; ++y) {
            // cout << '\n';
            for (int x = 0; x < width; ++x) {
                int index = (y * width + x) * 3;
                unsigned char r = data[index];
                unsigned char g = data[index+1];
                unsigned char b = data[index+2];
                this->matrizDeCores[y][x] = {
                    r,      // Red
                    g,  // Green
                    b,   // Blue
                    0
                };
                // cout << "[ " << static_cast<unsigned>(matrizDeCores[y][x].r) << " " << static_cast<unsigned>(matrizDeCores[y][x].g) << " " << static_cast<unsigned>(matrizDeCores[y][x].b) << " ], ";
                // cout << "[ " << data[index] << " " << data[index+1] << " " << data[index+2] << " ], ";
                // cout << "[ " << r << " " << g << " " << b << " ], ";
                // cout << "[ " << matrizDeCores[y][x].r << " " << matrizDeCores[y][x].g << " " << matrizDeCores[y][x].b << " ], ";

            }
        }

        cout << "finish" << endl;


    } else {
        // Handle error loading texture
        // For example, print an error message or throw an exception
        cout << "ERRO DATA NULA\n";
    }

    stbi_image_free(data);
}

void Texture::initializeMatrix(int w, int h) {
    this->matrizDeCores = new SDL_Color*[h];
    for (int i = 0; i < h; ++i) {
        this->matrizDeCores[i] = new SDL_Color[w];
    }
}

SDL_Color Texture::sample(Vec3 p){

    int x = static_cast<int> (p.x * w) % w; 
    int y = static_cast<int> (p.y * h) % h;

    return matrizDeCores[y][x];
}

void Texture::testColors() {
    for (int y = 0; y < h; ++y) {
        cout << "\n";
        for (int x = 0; x < w; ++x) {
            cout << "[ " << matrizDeCores[y][x].r << " " << matrizDeCores[y][x].g << " " << matrizDeCores[y][x].b << " ], ";
        }
    }
}