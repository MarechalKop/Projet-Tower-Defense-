#pragma once
#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <cmath>
#include <vector>
#include "stb_image.h"
#include <sil/sil.hpp>
#include <cstdlib>  // Pour std::rand()
#include <ctime>    // Pour std::time()

std::string recuperationNomFichierMap (std::ifstream& fichier);
void DessinCarte  (GLuint* tab, sil::Image image3, std::vector<std::vector<int>> indicesTexture );
std::vector<std::vector<int>> scanCartePourTexture (GLuint* tab, sil::Image image3);
