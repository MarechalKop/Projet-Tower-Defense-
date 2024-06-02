#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <sil/sil.hpp>


std::string premierMotDeLaligne(std::string const& str);
bool testValiditeITD (std::ifstream& fichier);
bool verifierSiLeFichierImageEstBienPresent (std::ifstream& fichier);
std::vector<std::string> split_string(std::string const& str);
bool valeursRGBValides (int R, int G, int B);
bool verifierCoordonneNoeud (int longueurImage, int largeur, int X, int Y);
bool verifierEntreeSortieExistent (sil::Image image);
