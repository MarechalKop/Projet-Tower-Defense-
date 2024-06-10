#include <iostream>
#include "ennemis.hpp"

void Ennemi::degatsEnnemi(int degats){
    pts_de_vie -= degats;
    if (pts_de_vie < 0){
        pts_de_vie = 0;
    }
}

bool Ennemi::estMort() const {
    return pts_de_vie <= 0;
}
