#pragma once
#include <fstream>
#include <vector>
#include <string>

std::string premierMotDeLaligne(std::string const& str);
bool verifierSiLesLignesDuFichierITDSontPresentesEtDansLeBonOrdre (std::ifstream& fichier);
bool verifierSiLeFichierImageEstBienPresent (std::ifstream& fichier);
std::vector<std::string> split_string(std::string const& str);
bool valeursRGBValides (int R, int G, int B);

