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

std::string recuperationNomFichierMap (std::ifstream& fichier);
void DessinCarte  (GLuint* tab, sil::Image image3);
