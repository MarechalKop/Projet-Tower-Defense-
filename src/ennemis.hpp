#pragma once

#include <string>

// Structure représentant un ennemi
struct EnnemiType1 {
    int pts_de_vie {};
    float vitesse {};
    int recompense {};
    std::string couleur {};

    void attaque(int degats);
    bool estMort();
};

struct EnnemiType2 {
    int pts_de_vie {};
    float vitesse {};
    int recompense {};
    std::string couleur {};

    void attaque(int degats);
    bool estMort();
};

