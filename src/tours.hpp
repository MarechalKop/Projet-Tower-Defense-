#pragma once
#include <ctime>
#include "ennemis.hpp" 

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

Tour creerTour(TypeTour type, int positionX, int positionY);

struct Projectile {
    float PositionX;
    float PositionY;
    float Cyblex;
    float Cybley;
    float tempsEcoule;
    float tempsTotal;
    int puissance;
    Ennemi* cible;    

    // Constructeur
    Projectile(float PositionInitialeX, float PositionInitialeY, float Cyblex, float Cybley, float tempsTotal, int puissance, Ennemi* cible)
        : PositionX(PositionInitialeX), PositionY(PositionInitialeY), Cyblex(Cyblex), Cybley(Cybley), tempsEcoule(0.0f), tempsTotal(tempsTotal), puissance(puissance), cible(cible){}

    // Méthode pour mettre à jour la position
    void updatePosition(float dt) {
        tempsEcoule += dt;
        float t = tempsEcoule / tempsTotal;  // tempsTotal est le temps que met le projectile pour atteindre sa cible
        PositionX = (1 - t) * PositionX + t * Cyblex;
        PositionY = (1 - t) * PositionY + t * Cybley;

    //     std::cout << "Coordonnee X de la cible "  << Cyblex << std::endl;
    //     std::cout << "Coordonnee Y de la cible "  << Cybley << std::endl;

<<<<<<< HEAD
        std::cout << "Mise a jour de la position du projectile : (" << PositionX << ", " << PositionY << ")" << std::endl;
        std::cout << "La valeur de tempsTotal est " << tempsTotal << std::endl;
=======
    // std::cout << "Mise a jour de la position du projectile : (" << PositionX << ", " << PositionY << ")" << std::endl;
    // std::cout << "La valeur de tempsTotal est " << tempsTotal << std::endl;
>>>>>>> 022ce88a9ab090f72d6e4d359f3315aeac324b79
    }

    bool cibleAtteinte() {
        // Calculer la distance entre la position actuelle et la cible
        float distance = std::sqrt(std::pow(PositionX - Cyblex, 2) + std::pow(PositionY - Cybley, 2));

<<<<<<< HEAD
        std::cout << "Distance du projectile a la cible : " << distance << std::endl;
=======
    // std::cout << "Distance du projectile a la cible : " << distance << std::endl;
>>>>>>> 022ce88a9ab090f72d6e4d359f3315aeac324b79

        if (distance <0.5f) {
            return true;
        }
        return false;
    }
};

