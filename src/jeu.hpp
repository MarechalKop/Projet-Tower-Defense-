#pragma once
#include <vector>
#include "tours.hpp"
#include "ennemis.hpp"

void tourAttaqueEnnemi(Tour& tour, Ennemi& ennemi);
void mettreAJourJeu(std::vector<Tour>& tours, std::vector<Ennemi>& ennemis, float dt);
void commencerNouvelleVague();
bool tousEnnemisMorts(std::vector<Ennemi>& ennemis);
bool ennemiAtteintFin(const std::vector<Ennemi>& ennemis, Graph::WeightedGraph* graph, int idDernierNoeud);
void finPartie();
void finVague(bool victoire);


namespace Jeu {
    extern int total_argent;
    extern std::vector<Ennemi> ennemis;
    extern std::vector<std::vector<Ennemi>> vaguesEnnemis;
    extern Graph::WeightedGraph* graph;
    extern int idDernierNoeud;
    extern int vagueActuelle;
    extern bool partieEnCours;
    extern bool vagueEnCours;
    extern float tempsDepuisFinVague;
}