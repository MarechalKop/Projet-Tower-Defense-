#include "graphe.hpp"
#include "ValiditeITD.hpp"
#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <stack>
#include <queue>


int main () {
    std::ifstream fichier ("level1.itd");
  verifierSiLesLignesDuFichierITDSontPresentesEtDansLeBonOrdre (fichier);
}