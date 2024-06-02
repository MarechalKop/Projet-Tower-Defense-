#include "ValiditeITD.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include <algorithm>
#include <list>
#include <numeric>   
#include <sstream>

// Pour identifier si toutes les lignes sont bien présente et dans le bon ordre, on va avoir besoin de mettre de côté le premier mot de la ligne

// On utilise pour ça une fonction que l'on a dû créer pour l'exercice 2 du TD 4 du S2 qui permet de découper du texte et on la modifie pour qu'elle ne garde que le premier mot, les autres mots étants inutile

std::vector<std::string> split_string(std::string const& str){
    auto const estCaractereEspace = [](char letter){ return letter == ' '; };
    std::vector<std::string> vectorstring;
    std::string::const_iterator premièreLettreDunMot =  str.begin();
    std::string::const_iterator espaceEntreLesMots;
    while (premièreLettreDunMot != str.end() )
    {
        std::string stringDeTravail;
        premièreLettreDunMot = std::find_if_not (premièreLettreDunMot,str.end(), estCaractereEspace);
        espaceEntreLesMots = std::find_if (premièreLettreDunMot,str.end(), estCaractereEspace);
        
       
       for (premièreLettreDunMot; premièreLettreDunMot != espaceEntreLesMots; premièreLettreDunMot++)
       {
        stringDeTravail.push_back(*premièreLettreDunMot);
       }

       vectorstring.push_back(stringDeTravail);
        premièreLettreDunMot = espaceEntreLesMots;
        stringDeTravail.clear();
    }
   

    return vectorstring;
}



std::string premierMotDeLaligne(std::string const& str){
    auto const estCaractereEspace = [](char letter){ return letter == ' '; };
    std::string::const_iterator premièreLettreDunMot =  str.begin();
    std::string::const_iterator espaceEntreLesMots;
  
    
        premièreLettreDunMot = std::find_if_not (premièreLettreDunMot,str.end(), estCaractereEspace);
        espaceEntreLesMots = std::find_if (premièreLettreDunMot,str.end(), estCaractereEspace);
        
       std::string premierMot (premièreLettreDunMot, espaceEntreLesMots);
       
    
    return premierMot;
}




bool valeursRGBValides (int R, int G, int B)
{
    bool validiteRGB = false;
    if ((R >= 0 && R <= 255) && (G >= 0 && G <= 255) && (B >= 0 && B <= 255) )
    {
        validiteRGB = true;
        return validiteRGB;
    }
    else 
    {
        return validiteRGB;
    }
}

bool verifierSiLeFichierImageEstBienPresent (std::ifstream& fichier)
{
   if (fichier.good())
   {
    return true;
   }

   else 
   {
    return false;
   }
}




bool verifierSiLesLignesDuFichierITDSontPresentesEtDansLeBonOrdre (std::ifstream& fichier) {
    // On définit l'odre attendu des lignes
    std::vector<std::string> ordreAttendu = {"ITD","map","path","in","out","graph","node"};
    
    // On vérifie si le document est bien ouvert
    if (!fichier.is_open())
    {
        std::cout <<"Erreur : nous n'avons pas reussi a ouvrir le fichier ITD" << std::endl;
        return 1;
    }
    // on va lire et stocker le contenu des lignes du fichier
    std::string contenuLigne {};
    int ligneActuelle {};
    
    // La boucle while permet de lire ligne par ligne le contenu du fichier et s'arrête à quand il n'y plus rien à lire
    while (std::getline(fichier,contenuLigne))
    {   
        
        
        // Afin d'éviter que le lecteur lise les lignes de commentaires 
        if (contenuLigne[0] == '#') 
        {
        continue;
        }

        // utile pour moi, pour vérifier si la lecture se passe bien
        std::cout << contenuLigne << '\n';

        // on regarde le premier mot de la ligne
        std::string PremierMotaComparer = premierMotDeLaligne(contenuLigne);
        std::vector DecoupageMot = split_string(contenuLigne);

        // on le compare avec le mot attendu, si ce n'est pas bon, on le dit
        if (PremierMotaComparer != ordreAttendu[ligneActuelle])
        {
            std::cout << "Erreur : La ligne " << ligneActuelle + 1 << " est incorrecte. Le mot attendu est " << ordreAttendu[ligneActuelle] << " au lieu de " << PremierMotaComparer << std::endl;
            return false;
        }

        // si nous sommes sur les lignes couleurs, on vérifié si les valeurs RGB sont justes
        if (PremierMotaComparer == "path" || PremierMotaComparer == "in" || PremierMotaComparer == "out")
        {
            bool lesValeursRGBSontElleValide = valeursRGBValides(std::stoi(DecoupageMot[1]),std::stoi(DecoupageMot[2]),std::stoi(DecoupageMot[3]));

            if (lesValeursRGBSontElleValide == false )
            {
                std::cout << "Erreur : La ligne " << ligneActuelle + 1 << " est incorrecte. Les valeurs RGB sont fausses " << std::endl;
            return false;
            }
        }


    if (PremierMotaComparer == "map")
    {
        std::string nomFichier = DecoupageMot[1];
        std::ifstream fichierImage("../../../images/" + nomFichier);
        bool imageDeLaMapExisteElleBien = verifierSiLeFichierImageEstBienPresent(fichierImage);

        if (imageDeLaMapExisteElleBien == false )
        {
            std::cout << "Erreur : La ligne " << ligneActuelle + 1 << " est incorrecte. L'image de la map n'est pas trouvable ou ne parvient pas a etre ouvrir " << std::endl;
            return false;
        }
    }


        // on passe à la ligne d'après
        ligneActuelle += 1;
        // si on dépasse le cadre de la lecture, on arrête la boucle while
        if (ligneActuelle >= ordreAttendu.size()) {
            break;
        }
    }
        // s'il manque des lignes dans notre fichier, on le dit
        if (ligneActuelle < ordreAttendu.size()) 
        {
            std::cout << "Erreur : Fichier incomplet. Il manque les lignes " << ligneActuelle + 1 << " a " << ordreAttendu.size() <<  std::endl;
            return false;
        }      

    std::cout << "Le fichier est valide." << std::endl;
    return true;
}









