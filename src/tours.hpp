#pragma once
#include <ctime>

enum TypeTour {
    TypeA,
    TypeB
};

struct Tour {
    int puissance {};
    int portee {};
    float cadence {};
    TypeTour type;
    // Position de la tour
    int posX;
    int posY;

    // Temps du dernier tir
    std::time_t dernierTir {};

    // Méthode pour vérifier si un ennemi est dans la portée de la tour
    bool estDansPortee(int cibleX, int cibleY) const;

    // Méthode pour vérifier si la tour peut tirer
    bool peutTirer() const;

    // Méthode pour mettre à jour le temps du dernier tir
    void miseAJourTempsTir();
};
