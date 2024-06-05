#pragma once

#include <string>
#include <cmath>

// Classe représentant une tour de défense
class Tour {
    int puissance;
    int portee;
    float cadence;

    // Constructeur pour initialiser une tour
    Tour(int p, int po, float c) {
        puissance = p;
        portee = po;
        cadence = c;
    }

    // Méthodes pour obtenir les attributs de la tour
    int getPuissance() const {
        return puissance;
    }

    int getPortee() const {
        return portee;
    }

    float getCadence() const {
        return cadence;
    }
}