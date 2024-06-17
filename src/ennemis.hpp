#pragma once
#include <string>
#include "graphe.hpp"

enum TypeEnnemi {
    Type1,
    Type2
};


struct Ennemi {
    int pts_de_vie {};
    float vitesse {};
    int recompense {};
    TypeEnnemi type;
    Graph::Node positionActuelle {}; // Utilisez Node pour la position actuelle
    Graph::Node positionProchaine {}; // Utilisez Node pour la position suivante
    std::vector<int> chemin {};
    float distance(Graph::Node a, Graph::Node b);
    Graph::WeightedGraph* graphe;
    

    void degatsEnnemi(int degats);
    bool estMort() const;
    bool aAtteintLaFin = false;
    bool aTouche = true;
    void bouger(float dt); // Ajoutez cette méthode pour le mouvement
    Graph::Node chercherProchainePosition();
    void setChemin(const std::vector<int>& nouveauChemin); 
    void avancer(float dt); // Ajoutez cette méthode pour avancer de case en case
    void initialiserEnnemi(Graph::WeightedGraph* graphe, const std::vector<int>& cheminLePlusCourt, TypeEnnemi type);

};

std::vector<Ennemi> creerEnnemis(int nombreEnnemis, TypeEnnemi type, Graph::WeightedGraph* graphe, const std::vector<int>& cheminLePlusCourt);
