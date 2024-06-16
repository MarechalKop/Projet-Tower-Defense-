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

Tour creerTour(TypeTour type, int positionX, int positionY) {
    Tour tour;
    if (type == TypeTour::TypeA) {
        tour.puissance = 50;
        tour.portee = 4; // Portée en distance de Chebyshev
        tour.cadence = 1.f; // Cadence de tir en dixièmes de seconde
    } else if (type == TypeTour::TypeB) {
        tour.puissance = 200;
        tour.portee = 6; // Portée en distance de Chebyshev
        tour.cadence = 25.f; // Cadence de tir en dixièmes de seconde
    }
    tour.type = type;
    tour.posX = positionX; // Position X de la tour sur la carte
    tour.posY = positionY; // Position Y de la tour sur la carte
    return tour;
    }
