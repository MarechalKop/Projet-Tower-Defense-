#include <iostream>
#include <ctime>
#include "tours.hpp"
#include "ennemis.hpp"
#include "jeu.hpp"

namespace Jeu {
    int total_argent {0};
}

void tourAttaqueEnnemi(Tour& tour, Ennemi& ennemi) {
    ennemi.degatsEnnemi(tour.puissance);
    if (ennemi.estMort()) {
        Jeu::total_argent += ennemi.recompense;
    }
}