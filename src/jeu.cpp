#include <iostream>
#include <ctime>
#include <vector>
#include "tours.hpp"
#include "ennemis.hpp"
#include "jeu.hpp"
#include "graphe.hpp"

namespace Jeu {
    int total_argent {0};
    std::vector<Ennemi> ennemis; // Ajoutez cette ligne
    std::vector<std::vector<Ennemi>> vaguesEnnemis; // Ajoutez cette ligne
    Graph::WeightedGraph* graph; // Ajoutez cette ligne
    int idDernierNoeud; // Ajoutez cette ligneS
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


// Ajoutez ces variables à votre espace de noms Jeu
bool partieEnCours = true;
bool vagueEnCours = false;
int vagueActuelle = 0;
std::vector<std::vector<Ennemi>> vaguesEnnemis; // Contient toutes les vagues d'ennemis

// Méthode pour commencer une nouvelle vague
void commencerNouvelleVague() {
    if (vagueActuelle < vaguesEnnemis.size()) {
        Jeu::ennemis = vaguesEnnemis[vagueActuelle];
        vagueEnCours = true;
        vagueActuelle++;
    }
}

// Méthode pour vérifier si tous les ennemis sont morts
bool tousEnnemisMorts() {
    for (const auto& ennemi : Jeu::ennemis) {
        if (!ennemi.estMort()) {
            return false;
        }
    }
    return true;
}

// Méthode pour vérifier si un ennemi a atteint le dernier noeud
bool ennemiAtteintFin() {
    for (const auto& ennemi : Jeu::ennemis) {
        if (ennemi.positionActuelle == Jeu::graph->getNodePosition(Jeu::idDernierNoeud)) {
            return true;
        }
    }
    return false;
}

// Méthode pour gérer la fin de la partie
void finPartie(bool victoire) {
    partieEnCours = false;
    if (victoire) {
        std::cout << "Félicitations, vous avez gagné !" << std::endl;
    } else {
        std::cout << "Vous avez perdu." << std::endl;
    }
}