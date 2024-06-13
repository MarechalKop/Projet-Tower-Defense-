#include <iostream>
#include <cmath>
#include <vector>
#include "ennemis.hpp"

const float epsilon = 0.001f;

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

     if (estMort()) {
        return;
    }

    // Vérifier si l'ennemi a atteint la position suivante
    if (distance(this->positionActuelle, this->positionProchaine) <= epsilon) {
        // Mettre à jour la position actuelle et chercher la prochaine position
        this->positionActuelle = this->positionProchaine;
        this->positionProchaine = chercherProchainePosition();
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

void Ennemi::initialiserEnnemi(Graph::WeightedGraph* graphe, const std::vector<int>& cheminLePlusCourt, TypeEnnemi type) {
    this->pts_de_vie = 100; // Par exemple
    this->vitesse = 100; // Par exemple
    this->recompense = 50; // Par exemple
    this->couleur = "rouge"; // Par exemple
    this->type = type; // Utilisez le type passé en paramètre
    this->graphe = graphe;

    if (!cheminLePlusCourt.empty()) {
        this->positionActuelle = graphe->getNodePosition(cheminLePlusCourt[0]);
        if (cheminLePlusCourt.size() > 1) {
            this->positionProchaine = graphe->getNodePosition(cheminLePlusCourt[1]);
        } else {
            this->positionProchaine = this->positionActuelle;
        }
        this->setChemin(cheminLePlusCourt);
        this->chercherProchainePosition(); // Initialiser la prochaine position
    }
}

std::vector<Ennemi> creerEnnemis(int nombreEnnemis, TypeEnnemi type, Graph::WeightedGraph* graphe, const std::vector<int>& cheminLePlusCourt) {
    std::vector<Ennemi> ennemis;
    for (int i = 0; i < nombreEnnemis; ++i) {
        Ennemi ennemi;
        ennemi.initialiserEnnemi(graphe, cheminLePlusCourt, type);
        ennemis.push_back(ennemi);
    }
    return ennemis;
}
