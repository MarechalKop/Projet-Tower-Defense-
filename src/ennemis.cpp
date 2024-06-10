#include <iostream>
#include <cmath>
#include "ennemis.hpp"

const float epsilon = 0.1f;

Graph::Node interpolationLineaire(Graph::Node a, Graph::Node b, float t) {
    Graph::Node result;
    result.x = a.x * (1.0f - t) + b.x * t;
    result.y = a.y * (1.0f - t) + b.y * t;
    return result;
}

void Ennemi::degatsEnnemi(int degats) {
    pts_de_vie -= degats;
    if (pts_de_vie < 0) {
        pts_de_vie = 0;
    }
}

bool Ennemi::estMort() const {
    return pts_de_vie <= 0;
}

float Ennemi::distance(Graph::Node a, Graph::Node b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
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
    if (distance(this->positionActuelle, this->positionProchaine) <= epsilon) {
        // Mettre à jour la position actuelle et chercher la prochaine position
        this->positionActuelle = this->positionProchaine;
        this->positionProchaine = chercherProchainePosition();
        std::cout << "Position actuelle: (" << this->positionActuelle.x << ", " << this->positionActuelle.y << ")" << std::endl;
        std::cout << "Prochaine position: (" << this->positionProchaine.x << ", " << this->positionProchaine.y << ")" << std::endl;
    } else {
        // Calculer la nouvelle position en utilisant une interpolation linéaire
        float totalDistance = distance(this->positionActuelle, this->positionProchaine);
        float travelDistance = this->vitesse * dt;

        if (travelDistance >= totalDistance) {
            this->positionActuelle = this->positionProchaine;
        } else {
            float t = travelDistance / totalDistance;
            this->positionActuelle = interpolationLineaire(this->positionActuelle, this->positionProchaine, t);
        }

        std::cout << "Position actuelle en mouvement: (" << this->positionActuelle.x << ", " << this->positionActuelle.y << ")" << std::endl;
        std::cout << "Distance avec la prochaine position : " << distance(this->positionActuelle, this->positionProchaine) << std::endl;
    }
}



Graph::Node Ennemi::chercherProchainePosition() {
    std::cout << "Chemin actuel : ";
    for (int n : this->chemin) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    if (!this->chemin.empty()) {
        int next_node = this->chemin.front();
        this->chemin.erase(this->chemin.begin());
        return this->graphe->getNodePosition(next_node);
    } else {
        return this->positionActuelle;
    }
}
