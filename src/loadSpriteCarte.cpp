#include "loadSpriteCarte.hpp"
#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <cmath>
#include <vector>
#include "stb_image.h"

GLuint* chargerTousLesSpritesCartes()
{
    int x, y, n;
    const int nombreTexture = 25; // Nombre de textures, ajusté pour inclure la nouvelle texture
    std::vector<unsigned char*> Result(nombreTexture);
    
    Result[0] = stbi_load("../../images/sprites/Tiles/Bleu.png", &x, &y, &n, 0);
    Result[1] = stbi_load("../../images/sprites/Tiles/Rouge.png", &x, &y, &n, 0);
    Result[2] = stbi_load("../../images/sprites/Tiles/T1.png", &x, &y, &n, 0);
    Result[3] = stbi_load("../../images/sprites/Tiles/T2.png", &x, &y, &n, 0);
    Result[4] = stbi_load("../../images/sprites/Tiles/T3.png", &x, &y, &n, 0);
    Result[5] = stbi_load("../../images/sprites/Tiles/T4.png", &x, &y, &n, 0);
    Result[6] = stbi_load("../../images/sprites/Tiles/T5.png", &x, &y, &n, 0);
    Result[7] = stbi_load("../../images/sprites/Tiles/T6.png", &x, &y, &n, 0);
    Result[8] = stbi_load("../../images/sprites/Tiles/T7.png", &x, &y, &n, 0);
    Result[9] = stbi_load("../../images/sprites/Tiles/T8.png", &x, &y, &n, 0);
    Result[10] = stbi_load("../../images/sprites/Tiles/T9.png", &x, &y, &n, 0);
    Result[11] = stbi_load("../../images/sprites/Tiles/T10.png", &x, &y, &n, 0);
    Result[12] = stbi_load("../../images/sprites/Tiles/T11.png", &x, &y, &n, 0);
    Result[13] = stbi_load("../../images/sprites/Tiles/T12.png", &x, &y, &n, 0);
    Result[14] = stbi_load("../../images/sprites/Tiles/T13.png", &x, &y, &n, 0);
    Result[15] = stbi_load("../../images/sprites/Tiles/T14.png", &x, &y, &n, 0);
    Result[16] = stbi_load("../../images/sprites/Tiles/T15.png", &x, &y, &n, 0);
    Result[17] = stbi_load("../../images/sprites/Tiles/T16.png", &x, &y, &n, 0);
    Result[18] = stbi_load("../../images/sprites/Tiles/T17.png", &x, &y, &n, 0);
    Result[19] = stbi_load("../../images/sprites/Tiles/T18.png", &x, &y, &n, 0);
    Result[20] = stbi_load("../../images/sprites/Tiles/T19.png", &x, &y, &n, 0);
    Result[21] = stbi_load("../../images/sprites/Tiles/T20.png", &x, &y, &n, 0);
    Result[22] = stbi_load("../../images/sprites/Tiles/T21.png", &x, &y, &n, 0);
    Result[23] = stbi_load("../../images/sprites/Tiles/T22.png", &x, &y, &n, 0);
    Result[24] = stbi_load("../../images/sprites/Tiles/T23.png", &x, &y, &n, 0);

    for (int i = 0; i < nombreTexture; i++) {
        if (Result[i] == nullptr) {
            std::cerr << "Erreur de chargement de la texture " << i << std::endl;
            return nullptr;
        } 
    }

    GLuint* tab = new GLuint[nombreTexture];
    glGenTextures(nombreTexture, tab);
// ...
for (int i = 0; i < nombreTexture; i++) {
    glBindTexture(GL_TEXTURE_2D, tab[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Utilisez le nombre de canaux que vous avez obtenu lors du chargement de l'image
    GLenum format;
    if (n == 4) {
        format = GL_RGBA;
    } else if (n == 3) {
        format = GL_RGB;
    } else {
        std::cerr << "Unsupported number of channels: " << n << std::endl;
        return nullptr;
    }

    glTexImage2D(
        GL_TEXTURE_2D, 0, format,
        x, y, 0, format, GL_UNSIGNED_BYTE, Result[i]
    );

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Erreur OpenGL lors du chargement de la texture " << i << ": " << error << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(Result[i]);
}
// ...


    return tab;
}
