#include <iostream>
#include <ctime>
#include <vector>
#include "tours.hpp"
#include "ennemis.hpp"
#include "jeu.hpp"
#include "graphe.hpp"

namespace Jeu {
    float total_argentEnFloat {100};
    int totalArgentInt;
    std::vector<Ennemi> ennemis;
    std::vector<std::vector<Ennemi>> vaguesEnnemis;
    Graph::WeightedGraph* graph;
    int idDernierNoeud;
    int vagueActuelle = 0;
    bool partieEnCours = true;
    bool vagueEnCours = false;
    float tempsDepuisFinVague = 0.0f;
    int prochainEnnemiAAfficher = 0;
    int points_de_vieJoueur = 3;
    
}




void tourAttaqueEnnemi(Tour& tour, Ennemi& ennemi) {
    if (tour.peutTirer() && tour.estDansPortee(ennemi.positionActuelle.x, ennemi.positionActuelle.y)) {
        ennemi.degatsEnnemi(tour.puissance);
        tour.miseAJourTempsTir();

        if (ennemi.estMort()) {
            Jeu::total_argentEnFloat += ennemi.recompense;
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



// Méthode pour commencer une nouvelle vague
void commencerNouvelleVague() {
    if (Jeu::vagueActuelle < Jeu::vaguesEnnemis.size()) {
        Jeu::ennemis = Jeu::vaguesEnnemis[Jeu::vagueActuelle];
        Jeu::vagueEnCours = true;
        Jeu::vagueActuelle++;
        Jeu::prochainEnnemiAAfficher = 0;
    }
}

// Méthode pour vérifier si tous les ennemis sont morts
bool tousEnnemisMorts(std::vector<Ennemi>& ennemis) {
    for (const auto& ennemi : ennemis) {
        if (!ennemi.estMort()) {
            return false;
        }
    }
    return true;
}

// Méthode pour vérifier si un ennemi a atteint le dernier noeud
bool ennemiAtteintFin(std::vector<Ennemi>& ennemis, Graph::WeightedGraph* graph, int idDernierNoeud)  {
    for (auto& ennemi : ennemis) {
        float distance = sqrt(pow(ennemi.positionActuelle.x - graph->getNodePosition(idDernierNoeud).x, 2) +
                              pow(ennemi.positionActuelle.y - graph->getNodePosition(idDernierNoeud).y, 2));
        if (distance <= 0.1 && ennemi.aAtteintLaFin != true) {  // Vérifie si l'ennemi a atteint la fin et n'a pas encore été comptabilisé
            ennemi.aAtteintLaFin = true;  // Marque l'ennemi comme ayant atteint la fin
            Jeu::points_de_vieJoueur--;  // Le joueur perd un point de vie
            return true;
        }
    }
    return false;
}





// Méthode pour gérer la fin de la partie
void finPartie() {
    // Si un ennemi atteint le dernier nœud, la partie se termine et le joueur perd
    if (Jeu::points_de_vieJoueur <= 0) {
        Jeu::partieEnCours = false;
        std::cout << "Vous avez perdu la partie." << std::endl;
    } 
    // Si tous les ennemis de la dernière vague sont morts, la partie se termine et le joueur gagne
    else if (Jeu::vagueActuelle == Jeu::vaguesEnnemis.size() - 1 && tousEnnemisMorts(Jeu::vaguesEnnemis[Jeu::vagueActuelle])) {
        Jeu::partieEnCours = false;
        std::cout << "Félicitations, vous avez gagné la partie !" << std::endl;
    }
}

void finVague(bool victoire) {
    Jeu::vagueEnCours = false;
    if (victoire) {
        std::cout << "Félicitations, vous avez terminé la vague !" << std::endl;
    } else {
        std::cout << "Vous avez perdu la vague." << std::endl;
    }
}