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
        Ennemi* ennemiPlusProche = nullptr;
        float distanceMin = std::numeric_limits<float>::max();

        for (auto& ennemi : ennemis) {
            if (!ennemi.estMort() && tour.estDansPortee(ennemi.positionActuelle.x, ennemi.positionActuelle.y)) {
                float distance = std::max(std::abs(ennemi.positionActuelle.x - tour.posX), std::abs(ennemi.positionActuelle.y - tour.posY));
                if (distance < distanceMin) {
                    distanceMin = distance;
                    ennemiPlusProche = &ennemi;
                }
            }
        }
        
        if (ennemiPlusProche && tour.peutTirer()) {
            tourAttaqueEnnemi(tour, *ennemiPlusProche);
            tour.miseAJourTempsTir();
        }
    }
}