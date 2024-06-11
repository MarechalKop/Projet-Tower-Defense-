#pragma once
#include <vector>
#include "tours.hpp"
#include "ennemis.hpp"

void tourAttaqueEnnemi(Tour& tour, Ennemi& ennemi);
void mettreAJourJeu(std::vector<Tour>& tours, std::vector<Ennemi>& ennemis, float dt);