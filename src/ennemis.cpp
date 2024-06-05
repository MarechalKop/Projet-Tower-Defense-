#include <iostream>
#include "ennemis.hpp"

// je sais pas du tout si c'est ce qu'il faut faire mais je mets au cas où

int main() {
    // Créer un ennemi avec des attributs spécifiques
    Ennemi ennemi1(100, 1.5f, 50, "rouge");

    // Afficher les attributs de l'ennemi
    std::cout << "Ennemi1 - Points de vie: " << ennemi1.getPV() << ", Vitesse: " << ennemi1.getVitesse() << ", Récompense: " << ennemi1.getRecompense() << ", Couleur: " << ennemi1.getCouleur() << std::endl;

    return 0;
}
