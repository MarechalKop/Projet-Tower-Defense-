#include <iostream>
#include "ennemis.hpp"

const float epsilon = 0.1;



Graph::Node interpolationLineaire(Graph::Node a, Graph::Node b, float t) {
    Graph::Node result;
    result.x = a.x * (1.0f - t) + b.x * t;
    result.y = a.y * (1.0f - t) + b.y * t;
    return result;
}

void Ennemi::degatsEnnemi(int degats){
    pts_de_vie -= degats;
    if (pts_de_vie < 0){
        pts_de_vie = 0;
    }
}

bool Ennemi::estMort() const {
    return pts_de_vie <= 0;
}

float Ennemi::distance(Graph::Node a, Graph::Node b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

void Ennemi::setChemin(const std::vector<int>& nouveauChemin) {
    this->chemin = nouveauChemin;
}

void Ennemi::bouger(float dt) {
    // Calculer la nouvelle position en utilisant une interpolation linéaire
    this->positionActuelle = interpolationLineaire(this->positionActuelle, this->positionProchaine, dt);

    // Vérifier si l'ennemi a atteint la position suivante
    if (distance(this->positionActuelle, this->positionProchaine) < epsilon) {
        // Mettre à jour la position actuelle et la position suivante
        this->positionActuelle = this->positionProchaine;
        this->positionProchaine = chercherProchainePosition();
    }
}

void Ennemi::avancer(float dt) {
    // Vérifier si l'ennemi a atteint la position suivante
    if (distance(this->positionActuelle, this->positionProchaine) < epsilon) {
        // Mettre à jour la position actuelle et la position suivante
        this->positionActuelle = this->positionProchaine;
        this->positionProchaine = chercherProchainePosition();
    } else {
        // Calculer la nouvelle position en utilisant une interpolation linéaire
        this->positionActuelle = interpolationLineaire(this->positionActuelle, this->positionProchaine, this->vitesse * dt);
    }
}


Graph::Node Ennemi::chercherProchainePosition() {
    if (!this->chemin.empty()) {
        int next_node = this->chemin.front();
        this->chemin.erase(this->chemin.begin());
        return this->graphe->getNodePosition(next_node);
    } else {
        return this->positionActuelle;
    }
}