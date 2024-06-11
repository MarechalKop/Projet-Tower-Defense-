#include <iostream>
#include <ctime>
#include <vector>
#include "tours.hpp"
#include "ennemis.hpp"
#include "jeu.hpp"
#include "graphe.hpp"

namespace Jeu {
    int total_argent {0};
}

void tourAttaqueEnnemi(Tour& tour, Ennemi& ennemi) {
    if (tour.peutTirer() && tour.estDansPortee(ennemi.positionActuelle.x, ennemi.positionActuelle.y)) {
        ennemi.degatsEnnemi(tour.puissance);
        tour.miseAJourTempsTir();

        if (ennemi.estMort()) {
            Jeu::total_argent += ennemi.recompense;
        }
    }
}

void mettreAJourJeu(std::vector<Tour>& tours, std::vector<Ennemi>& ennemis, float dt) {
    // Mettre à jour les positions des ennemis
    for (auto& ennemi : ennemis) {
        ennemi.avancer(dt);
    }

    // Faire tirer les tours sur les ennemis à portée
    for (auto& tour : tours) {
        for (auto& ennemi : ennemis) {
            if (!ennemi.estMort()) {
                tourAttaqueEnnemi(tour, ennemi);
            }
        }
    }
}