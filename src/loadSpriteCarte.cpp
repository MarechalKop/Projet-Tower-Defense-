#include "loadSpriteCarte.hpp"
#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <cmath>
#include <vector>
#include "stb_image.h"
GLuint* chargerTousLesSprites () 
{
    int x {};
    int y {};
    int n {};
    std::vector<unsigned char *> Result(4);
    Result[0] = stbi_load( "../../images/c.png",& x,& y,& n, 0);
    Result[1] = stbi_load( "../../images/c.png",& x,& y,& n, 0);
    Result[2] = stbi_load( "../../images/sprites/Tiles/FieldsTile_38.png",& x,& y,& n, 0);
    Result[3] = stbi_load( "../../images/sprites/Tiles/FieldsTile_46.png",& x,& y,& n, 0);
    
    if (Result[0] == 0 || Result[1] == 0 || Result[2] == 0 || Result[3] == 0)
    {
        std::cout << "Il y a une erreur chacal" << std::endl;
    }
    else 
    {
        std::cout << "C'est ok bg" << std::endl;
    }

    int const nombreTexture = 4;
    GLuint* tab = new GLuint[nombreTexture]; 
    
    
    glGenTextures(nombreTexture, tab); 

    for (int i {}; i < nombreTexture; i++)
    { 
    glBindTexture(GL_TEXTURE_2D, tab[i] );
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(
     GL_TEXTURE_2D, 0 , GL_RGB,
        x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, Result[i]);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(Result[i]);
    }

    return tab;
}
