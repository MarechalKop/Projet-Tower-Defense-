#pragma once

#include <string>

// Classe représentant un ennemi
class Ennemi {
    int pts_de_vie;
    float vitesse;
    int recompense;
    std::string couleur;

    // Constructeur pour initialiser un ennemi
    Ennemi(int pv, float v, int r, const std::string& c) {
        pts_de_vie = pv;
        vitesse = v;
        recompense = r;
        couleur = c;
    }

    // Méthodes pour obtenir les attributs de l'ennemi
    int getPV() const {
        return pts_de_vie;
    }

    float getVitesse() const {
        return vitesse;
    }

    int getRecompense() const {
        return recompense;
    }

    std::string getCouleur() const {
        return couleur;
    }

};
