#include <iostream>
#include "ennemis.hpp"
#include "tours.hpp"

// variable argent pour faire genre, faudra ptet le déplacer autre part
namespace Jeu {
    int total_argent {0};
}

void Ennemi::degatsEnnemi(int degats){
    pts_de_vie -= degats;
    if (pts_de_vie < 0){
        pts_de_vie = 0;
    }
}

bool Ennemi::estMort() const {
    return pts_de_vie <= 0;
}

void tourAttaqueEnnemi(Tour& tour, Ennemi& ennemi) {
    ennemi.degatsEnnemi(tour.puissance);
    if (ennemi.estMort()) {
        Jeu::total_argent += ennemi.recompense;
    }
}
