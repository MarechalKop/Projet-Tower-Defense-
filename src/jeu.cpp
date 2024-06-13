#include <iostream>
#include <ctime>
#include <vector>
#include "tours.hpp"
#include "ennemis.hpp"
#include "jeu.hpp"
#include "graphe.hpp"

namespace Jeu {
    int total_argent {0};
    std::vector<Ennemi> ennemis;
    std::vector<std::vector<Ennemi>> vaguesEnnemis;
    Graph::WeightedGraph* graph;
    int idDernierNoeud;
    int vagueActuelle = 0;
    bool partieEnCours = true;
    bool vagueEnCours = false;
    float tempsDepuisFinVague = 0.0f;
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



// Méthode pour commencer une nouvelle vague
void commencerNouvelleVague() {
    if (Jeu::vagueActuelle < Jeu::vaguesEnnemis.size()) {
        Jeu::ennemis = Jeu::vaguesEnnemis[Jeu::vagueActuelle];
        Jeu::vagueEnCours = true;
        Jeu::vagueActuelle++;
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
bool ennemiAtteintFin(const std::vector<Ennemi>& ennemis, Graph::WeightedGraph* graph, int idDernierNoeud) {
    for (const auto& ennemi : ennemis) {
        float distance = sqrt(pow(ennemi.positionActuelle.x - graph->getNodePosition(idDernierNoeud).x, 2) +
                              pow(ennemi.positionActuelle.y - graph->getNodePosition(idDernierNoeud).y, 2));
        if (distance < 0.5) {  // Remplacez 0.1 par le seuil approprié pour votre jeu
            return true;
        }
    }
    return false;
}




// Méthode pour gérer la fin de la partie
void finPartie() {
    // Si un ennemi atteint le dernier nœud, la partie se termine et le joueur perd
    if (ennemiAtteintFin(Jeu::vaguesEnnemis[Jeu::vagueActuelle], Jeu::graph, Jeu::idDernierNoeud)) {
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