#include <iostream>
#include <cmath>
#include <ctime>
#include "tours.hpp"
#include "ennemis.hpp"

bool Tour::estDansPortee(int cibleX, int cibleY) const {
    int distance_Chebyshev = std::max(std::abs(cibleX - posX), std::abs(cibleY - posY));

    // Vérifier si la distance est inférieure ou égale à la portée de la tour
    return distance_Chebyshev <= portee;
}

bool Tour::peutTirer() const {
    std::time_t maintenant = std::time(nullptr);
    double intervalle = std::difftime(maintenant, dernierTir);

    // Vérifier si le temps écoulé depuis le dernier tir de la tour est suffisant pour permettre un nouveau tir
    return intervalle >= (cadence * 0.1);
}

void Tour::miseAJourTempsTir() {
    dernierTir = std::time(nullptr);
}