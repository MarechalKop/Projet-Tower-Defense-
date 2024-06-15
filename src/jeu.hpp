#pragma once
#include <vector>
#include "tours.hpp"
#include "ennemis.hpp"

void tourAttaqueEnnemi(Tour& tour, Ennemi& ennemi);
void mettreAJourTour(std::vector<Tour>& tours, std::vector<Ennemi>& ennemis, float dt);
void commencerNouvelleVague();
bool tousEnnemisMorts(std::vector<Ennemi>& ennemis);
bool ennemiAtteintFin(std::vector<Ennemi>& ennemis, Graph::WeightedGraph* graph, int idDernierNoeud);
void finPartie();
void finVague(bool victoire);
bool UnennemiALaFin(std::vector<Ennemi>& ennemis, Graph::WeightedGraph* graph, int idDernierNoeud);


namespace Jeu {
    extern float total_argentEnFloat ;
    extern std::vector<Ennemi> ennemis;
    extern std::vector<std::vector<Ennemi>> vaguesEnnemis;
    extern Graph::WeightedGraph* graph;
    extern int idDernierNoeud;
    extern int vagueActuelle;
    extern bool partieEnCours;
    extern bool vagueEnCours;
    extern float tempsDepuisFinVague;
    extern int prochainEnnemiAAfficher;
    extern int points_de_vieJoueur;
    extern int totalArgentInt;
    extern std::vector<Projectile> projectiles;
    extern float tempsTotalFlèche;
}