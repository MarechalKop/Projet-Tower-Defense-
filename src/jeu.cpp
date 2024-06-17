#include <iostream>
#include <ctime>
#include <vector>
#include "tours.hpp"
#include "ennemis.hpp"
#include "jeu.hpp"
#include "graphe.hpp"

namespace Jeu {
    int points_de_vieJoueur = 3;
    int prochainEnnemiAAfficher = 0;
    float tempsDepuisFinVague = 0.0f;
    bool vagueEnCours = false;
    bool partieEnCours = true;
    int vagueActuelle = 0;
    int idDernierNoeud;
    Graph::WeightedGraph* graph;
    std::vector<std::vector<Ennemi>> vaguesEnnemis;
    std::vector<Ennemi> ennemis;
    int totalArgentInt;
    float total_argentEnFloat {100};
    float tempsTotalFlèche = 0.005;
    std::vector<Projectile> projectiles;
	int finDuJeuVictorieuse = -1;
}

void tourAttaqueEnnemi(Tour& tour, Ennemi& ennemi) {
    if (tour.peutTirer() && tour.estDansPortee(ennemi.positionActuelle.x, ennemi.positionActuelle.y) && ennemi.aTouche && !ennemi.aAtteintLaFin) {
       
        tour.miseAJourTempsTir();

        Projectile projectile(tour.posX, tour.posY + 0.8, ennemi.positionActuelle.x, ennemi.positionActuelle.y, Jeu::tempsTotalFlèche, tour.puissance, &ennemi);
        Jeu::projectiles.push_back(projectile);
        // std::cout << "Projectile ajouté à la liste" << std::endl;
        // std::cout << "Projectile ajouté. Nombre total de projectiles : " << Jeu::projectiles.size() << std::endl;
        // std::cout << "Projectile lancé de (" << tour.posX << ", " << tour.posY << ") vers (" << ennemi.positionActuelle.x << ", " << ennemi.positionActuelle.y << ")" << std::endl;
    }
}

void mettreAJourTour(std::vector<Tour>& tours, std::vector<Ennemi>& ennemis, float dt) {
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
bool ennemiAtteintFin(std::vector<Ennemi>& ennemis, Graph::WeightedGraph* graph, int idDernierNoeud) {
    for (auto& ennemi : ennemis) {
        float distance = sqrt(pow(ennemi.positionActuelle.x - graph->getNodePosition(idDernierNoeud).x, 2) +
                              pow(ennemi.positionActuelle.y - graph->getNodePosition(idDernierNoeud).y, 2));
        if (distance <= 0.1 && ennemi.aAtteintLaFin != true) {  // Vérifie si l'ennemi a atteint la fin et n'a pas encore été comptabilisé
            ennemi.aAtteintLaFin = true;  // Marque l'ennemi comme ayant atteint la fin
            Jeu::points_de_vieJoueur--;  // Le joueur perd un point de vie
			ennemi.pts_de_vie -= 1000;
			// Jeu::total_argentEnFloat -= ennemi.recompense;
            return true;
        }
    }
    return false;
}

bool UnennemiALaFin(std::vector<Ennemi>& ennemis, Graph::WeightedGraph* graph, int idDernierNoeud) {
    for (auto& ennemi : ennemis) {
        float distance = sqrt(pow(ennemi.positionActuelle.x - graph->getNodePosition(idDernierNoeud).x, 2) +
                              pow(ennemi.positionActuelle.y - graph->getNodePosition(idDernierNoeud).y, 2));
        if (distance <= 0.1) {  // Vérifie si l'ennemi a atteint la fin et n'a pas encore été comptabilisé
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
		Jeu::finDuJeuVictorieuse = 2;
        // std::cout << "Vous avez perdu la partie." << std::endl;
    } 
    // Si tous les ennemis de la dernière vague sont morts, la partie se termine et le joueur gagne
    else if (Jeu::vagueActuelle == Jeu::vaguesEnnemis.size() - 1 && tousEnnemisMorts(Jeu::vaguesEnnemis[Jeu::vagueActuelle])) {
		Jeu::finDuJeuVictorieuse = 1;
        Jeu::partieEnCours = false;
        //std::cout << "Felicitations, vous avez gagne la partie !" << std::endl;
    }      
}

void finVague(bool victoire) {
    Jeu::vagueEnCours = false;
    if (victoire) {
        // std::cout << "Felicitations, vous avez termine la vague !" << std::endl;
    } else {
        // std::cout << "Vous avez perdu la vague." << std::endl;
    }
}

std::vector<std::pair<int,int>> CreationVectorPeutOnPlacerTourIci() {
	std::vector<std::pair<int,int>> PeutOnPlacerTourIci;

    PeutOnPlacerTourIci.push_back(std::make_pair(-4,7));
	PeutOnPlacerTourIci.push_back(std::make_pair(-3,7));
	PeutOnPlacerTourIci.push_back(std::make_pair(-2,7));
	PeutOnPlacerTourIci.push_back(std::make_pair(-1,7));
	PeutOnPlacerTourIci.push_back(std::make_pair(6,7));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,7));
	PeutOnPlacerTourIci.push_back(std::make_pair(-4,6));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,6));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,5));
	PeutOnPlacerTourIci.push_back(std::make_pair(-7,2));
	PeutOnPlacerTourIci.push_back(std::make_pair(-7,1));
	PeutOnPlacerTourIci.push_back(std::make_pair(-7,0));
	PeutOnPlacerTourIci.push_back(std::make_pair(-7,-7));
	PeutOnPlacerTourIci.push_back(std::make_pair(-7,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(-6,8));
	PeutOnPlacerTourIci.push_back(std::make_pair(-6,-7));
	PeutOnPlacerTourIci.push_back(std::make_pair(-6,1));
	PeutOnPlacerTourIci.push_back(std::make_pair(-6,2));
	PeutOnPlacerTourIci.push_back(std::make_pair(-5,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(-5,-4));
	PeutOnPlacerTourIci.push_back(std::make_pair(-5,1));
	PeutOnPlacerTourIci.push_back(std::make_pair(-5,2));
	PeutOnPlacerTourIci.push_back(std::make_pair(-4,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(-4,4));
	PeutOnPlacerTourIci.push_back(std::make_pair(-4,-3));
	PeutOnPlacerTourIci.push_back(std::make_pair(-4,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(-4,1));
	PeutOnPlacerTourIci.push_back(std::make_pair(-4,2));
	PeutOnPlacerTourIci.push_back(std::make_pair(-3,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(-3,-7));
	PeutOnPlacerTourIci.push_back(std::make_pair(-3,-4));
	PeutOnPlacerTourIci.push_back(std::make_pair(-3,-3));
	PeutOnPlacerTourIci.push_back(std::make_pair(-3,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(-3,2));
	PeutOnPlacerTourIci.push_back(std::make_pair(-2,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(-2,-7));
	PeutOnPlacerTourIci.push_back(std::make_pair(-2,-6));
	PeutOnPlacerTourIci.push_back(std::make_pair(-2,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(-1,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(-1,-7));
	PeutOnPlacerTourIci.push_back(std::make_pair(-1,-6));
	PeutOnPlacerTourIci.push_back(std::make_pair(-1,2));
	PeutOnPlacerTourIci.push_back(std::make_pair(0,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(0,-7));
	PeutOnPlacerTourIci.push_back(std::make_pair(0,-6));
	PeutOnPlacerTourIci.push_back(std::make_pair(0,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(0,2));
	PeutOnPlacerTourIci.push_back(std::make_pair(0,3));
	PeutOnPlacerTourIci.push_back(std::make_pair(1,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(1,-7));
	PeutOnPlacerTourIci.push_back(std::make_pair(1,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(1,2));
	PeutOnPlacerTourIci.push_back(std::make_pair(1,3));
	PeutOnPlacerTourIci.push_back(std::make_pair(2,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(2,-7));
	PeutOnPlacerTourIci.push_back(std::make_pair(2,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(2,2));
	PeutOnPlacerTourIci.push_back(std::make_pair(2,3));
	PeutOnPlacerTourIci.push_back(std::make_pair(2,4));
	PeutOnPlacerTourIci.push_back(std::make_pair(3,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(3,-7));
	PeutOnPlacerTourIci.push_back(std::make_pair(3,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(3,3));
	PeutOnPlacerTourIci.push_back(std::make_pair(4,-3));
	PeutOnPlacerTourIci.push_back(std::make_pair(4,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(5,-4));
	PeutOnPlacerTourIci.push_back(std::make_pair(5,-3));
	PeutOnPlacerTourIci.push_back(std::make_pair(5,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(6,-4));
	PeutOnPlacerTourIci.push_back(std::make_pair(6,-3));
	PeutOnPlacerTourIci.push_back(std::make_pair(6,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(6,-1));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,-7));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,-6));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,-5));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,-4));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,-3));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,-1));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,0));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,1));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,2));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,3));
	PeutOnPlacerTourIci.push_back(std::make_pair(7,4));
	PeutOnPlacerTourIci.push_back(std::make_pair(-3,6));
	PeutOnPlacerTourIci.push_back(std::make_pair(-1,6));
	PeutOnPlacerTourIci.push_back(std::make_pair(-6,-8));
	PeutOnPlacerTourIci.push_back(std::make_pair(-4,-4));
	PeutOnPlacerTourIci.push_back(std::make_pair(-1,-2));
	PeutOnPlacerTourIci.push_back(std::make_pair(-1,3));
	PeutOnPlacerTourIci.push_back(std::make_pair(-2,2));

	return PeutOnPlacerTourIci;
}