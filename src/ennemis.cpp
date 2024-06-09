#include <iostream>
#include "ennemis.hpp"

// variable argent pour faire genre, faudra ptet le déplacer autre part
int total_argent {0};

void EnnemiType1::attaque(int degats){
    pts_de_vie -= degats;

    if (pts_de_vie < 0){
        pts_de_vie = 0;
    }

    if estMort(){
        total_argent += recompense;
    }
}
bool EnnemiType1::estMort() {
    return pts_de_vie <= 0;
}

void EnnemiType2::attaque(int degats){
    pts_de_vie -= degats;

    if (pts_de_vie < 0){
        pts_de_vie = 0;
    }

    if estMort(){
        total_argent += recompense;
    }
}
bool EnnemiType2::estMort() {
    return pts_de_vie <= 0;
}