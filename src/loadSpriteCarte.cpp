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
    const int nombreTexture = 4; // Nombre de textures, ajusté pour inclure la nouvelle texture
    std::vector<unsigned char*> Result(nombreTexture);
    
    Result[0] = stbi_load("../../images/sprites/Tiles/Bleu.png", &x, &y, &n, 0);
    Result[1] = stbi_load("../../images/sprites/Tiles/Rouge.png", &x, &y, &n, 0);
    Result[2] = stbi_load("../../images/sprites/Tiles/FieldsTile_38.png", &x, &y, &n, 0);
    Result[3] = stbi_load("../../images/sprites/Tiles/FieldsTile_46.png", &x, &y, &n, 0);
    // Result[4] = stbi_load("../../images/tank1.png", &x, &y, &n, 0); // Nouvelle texture
    // Result[4] = stbi_load("../../images/sprites/Units/1/U_Preattack.png", &x, &y, &n, 0);

    for (int i = 0; i < nombreTexture; i++) {
        if (Result[i] == nullptr) {
            std::cerr << "Erreur de chargement de la texture " << i << std::endl;
            return nullptr;
        } else {
            std::cout << "Texture " << i << " chargée avec succès : Dimensions (" << x << ", " << y << "), Canaux : " << n << std::endl;
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
