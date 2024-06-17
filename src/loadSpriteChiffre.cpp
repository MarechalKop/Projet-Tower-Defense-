#include "loadSpriteCarte.hpp"
#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <cmath>
#include <vector>
#include "stb_image.h"

GLuint* chargerTousLesSpritesChiffre()
{
    //int x, y, n;
    const int nombreTexture = 12; // Nombre de textures, ajusté pour inclure la nouvelle texture
    std::vector<unsigned char*> Result2(nombreTexture);
    std::vector<int> widths(nombreTexture), heights(nombreTexture), channels(nombreTexture);
    
    
    Result2[0] = stbi_load("../../images/0.png", &widths[0], &heights[0], &channels[0], 0);
    // Texture d'une tour
    Result2[1] = stbi_load("../../images/1.png", &widths[1], &heights[1], &channels[1], 0);
    Result2[2] = stbi_load("../../images/2.png", &widths[2], &heights[2], &channels[2], 0);
    Result2[3] = stbi_load("../../images/3.png", &widths[3], &heights[3], &channels[3], 0);
    Result2[4] = stbi_load("../../images/4.png", &widths[4], &heights[4], &channels[4], 0);
    Result2[5] = stbi_load("../../images/5.png", &widths[5], &heights[5], &channels[5], 0);
    Result2[6] = stbi_load("../../images/6.png", &widths[6], &heights[6], &channels[6], 0);
    Result2[7] = stbi_load("../../images/7.png", &widths[7], &heights[7], &channels[7], 0);
    Result2[8] = stbi_load("../../images/8.png", &widths[8], &heights[8], &channels[8], 0);
    Result2[9] = stbi_load("../../images/9.png", &widths[9], &heights[9], &channels[9], 0);
    Result2[10] = stbi_load("../../images/A.png", &widths[10], &heights[10], &channels[10], 0);
    Result2[11] = stbi_load("../../images/Z.png", &widths[11], &heights[11], &channels[11], 0);
   
    for (int i = 0; i < nombreTexture; i++) {
        if (Result2[i] == nullptr) {
            std::cerr << "Erreur de chargement de la texture de jeu " << i << std::endl;
            return nullptr;
        }
    }

    GLuint* tab2 = new GLuint[nombreTexture];
    glGenTextures(nombreTexture, tab2);
// ...
for (int i = 0; i < nombreTexture; i++) {
    glBindTexture(GL_TEXTURE_2D, tab2[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Utilisez le nombre de canaux que vous avez obtenu lors du chargement de l'image
    GLenum format;
    if (channels[i] == 4) {
        format = GL_RGBA;
    } else if (channels[i] == 3) {
        format = GL_RGB;
    } else {
        std::cerr << "Unsupported number of channels: " << channels[i] << std::endl;
        return nullptr;
    }

    glTexImage2D(
        GL_TEXTURE_2D, 0, format,
        widths[i], heights[i], 0, format, GL_UNSIGNED_BYTE, Result2[i]
    );

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Erreur OpenGL lors du chargement de la texture " << i << ": " << error << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(Result2[i]);
}
// ...


    return tab2;
}
