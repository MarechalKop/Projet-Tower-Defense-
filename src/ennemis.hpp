#pragma once
#include <string>

enum TypeEnnemi {
    Type1,
    Type2
};

struct Ennemi {
    int pts_de_vie {};
    float vitesse {};
    int recompense {};
    std::string couleur {};
    TypeEnnemi type;

    void degatsEnnemi(int degats);
    bool estMort() const;
};
