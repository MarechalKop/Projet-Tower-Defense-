#include "loadSpriteCarte.hpp"
#include "dessinerCarte.hpp"
#include "ValiditeITD.hpp"
#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <cmath>
#include <vector>
#include "stb_image.h"


std::string recuperationNomFichierMap(std::ifstream& fichier) {
    // On définit l'odre attendu des lignes
    std::vector<std::string> ordreAttendu = {"ITD","map","path","in","out","graph","node"};
    
    // On vérifie si le document est bien ouvert
    if (!fichier.is_open())
    {
        std::cout <<"Erreur : nous n'avons pas reussi a ouvrir le fichier ITD" << std::endl;
        return "";
    }
    // on va lire et stocker le contenu des lignes du fichier
    std::string contenuLigne {};
    int ligneActuelle {};

    std::string nomMap ="";

    // La boucle while permet de lire ligne par ligne le contenu du fichier et s'arrête à quand il n'y plus rien à lire
    while (std::getline(fichier,contenuLigne))
    {   
        // Afin d'éviter que le lecteur lise les lignes de commentaires 
        if (contenuLigne[0] == '#') 
        {
            continue;
        }

        // on regarde le premier mot de la ligne
        std::string PremierMotaComparer = premierMotDeLaligne(contenuLigne);
        std::vector DecoupageMot = split_string(contenuLigne);

        if (PremierMotaComparer == "map")
        {
            nomMap = DecoupageMot[1];
            
            break;  // On peut arrêter la lecture du fichier une fois qu'on a trouvé le nom de la carte
        }

        // on passe à la ligne d'après
        ligneActuelle += 1;
    }

    return nomMap;
}


 std::vector<std::vector<int>> scanCartePourTexture (GLuint* tab, sil::Image image3) {
    
		 std::srand(std::time(0));  
		
	
    std::vector<std::vector<int>> indicesTexture(image3.width(), std::vector<int>(image3.height()));

// Générez les indices de texture une seule fois
    for (int y = 0; y < image3.height(); y++) {
    for (int x = 0; x < image3.width(); x++) {
        if (image3.pixel(x, y).r >= 0.98 && image3.pixel(x, y).r <= 1 && 
            image3.pixel(x, y).g >= 0.98 && image3.pixel(x, y).g <= 1 && 
            image3.pixel(x, y).b >= 0.98 && image3.pixel(x, y).b <= 1) 
            {
            int choixT1[] = {2, 12, 13, 17};  // Vos choix
            int taille = sizeof(choixT1) / sizeof(choixT1[0]);  // Nombre de choix
            int index = std::rand() % taille;  // Génère un index aléatoire
            indicesTexture[x][y] = choixT1[index]; 
            }



          if (image3.pixel(x, y).r >= 0.3 && image3.pixel(x, y).g <= 0.4 && 
            image3.pixel(x, y).g == 0 &&
            image3.pixel(x, y).b == 1)
         {
            int choixT1[] = {2, 12, 13, 17};  // Vos choix
            int taille = sizeof(choixT1) / sizeof(choixT1[0]);  // Nombre de choix
            int index = std::rand() % taille;  // Génère un index aléatoire
            indicesTexture[x][y] = choixT1[index]; 
         }



         if (image3.pixel(x, y).r == 0 && image3.pixel(x,y).g == 0 && image3.pixel(x, y).b == 1)
         {
            indicesTexture[x][y] = 0; 
         }

         if (image3.pixel(x, y).r == 1 && image3.pixel(x,y).g == 0 && image3.pixel(x, y).b == 0)
         {
            indicesTexture[x][y] = 1; 
         }

         if (image3.pixel(x, y).r == 0 && image3.pixel(x,y).g == 0 && image3.pixel(x, y).b == 0)
         {
            indicesTexture[x][y] = 23; 
         }

         if (image3.pixel(x, y).r == 1 && image3.pixel(x,y).g == 1 && image3.pixel(x, y).b == 0)
         {
            int choixT1[] = {3, 4, 5};  // Vos choix
            int taille = sizeof(choixT1) / sizeof(choixT1[0]);  // Nombre de choix
            int index = std::rand() % taille;  // Génère un index aléatoire
            indicesTexture[x][y] = choixT1[index]; 
         }

         if (image3.pixel(x, y).r == 0 && image3.pixel(x,y).g == 1 && image3.pixel(x, y).b == 1)
         {
            int choixT1[] = {7, 11, 15};  // Vos choix
            int taille = sizeof(choixT1) / sizeof(choixT1[0]);  // Nombre de choix
            int index = std::rand() % taille;  // Génère un index aléatoire
            indicesTexture[x][y] = choixT1[index]; 
         }

          if (image3.pixel(x, y).r == 1 && 
            image3.pixel(x, y).g >= 0.3 && image3.pixel(x, y).g <= 0.4 && 
            image3.pixel(x, y).b >= 0.3 && image3.pixel(x, y).b <= 0.4)
         {
            indicesTexture[x][y] = 9; 
         }

          if (image3.pixel(x, y).r == 0 && image3.pixel(x,y).g == 1 && image3.pixel(x, y).b == 0)
         {
            int choixT1[] = {10, 14, 19};  // Vos choix
            int taille = sizeof(choixT1) / sizeof(choixT1[0]);  // Nombre de choix
            int index = std::rand() % taille;  // Génère un index aléatoire
            indicesTexture[x][y] = choixT1[index]; 
         }

       


           if (image3.pixel(x, y).r >= 0.3 && image3.pixel(x, y).g <= 0.4 &&
            image3.pixel(x, y).g >= 0.3 && image3.pixel(x, y).g <= 0.4
            && image3.pixel(x, y).b == 0 )
         {
            int choixT1[] = {18, 24};  // Vos choix
            int taille = sizeof(choixT1) / sizeof(choixT1[0]);  // Nombre de choix
            int index = std::rand() % taille;  // Génère un index aléatoire
            indicesTexture[x][y] = choixT1[index]; 
         }

          if (image3.pixel(x, y).r >= 0.3 && image3.pixel(x, y).g <= 0.4 && 
            image3.pixel(x, y).g == 0 &&
            image3.pixel(x, y).b >= 0.3 && image3.pixel(x, y).b <= 0.4)
         {
            int choixT1[] = {6, 8};  // Vos choix
            int taille = sizeof(choixT1) / sizeof(choixT1[0]);  // Nombre de choix
            int index = std::rand() % taille;  // Génère un index aléatoire
            indicesTexture[x][y] = choixT1[index]; 
         }


            if (image3.pixel(x, y).r == 0  && 
            image3.pixel(x, y).g >= 0.3 && image3.pixel(x, y).g <= 0.4 &&
            image3.pixel(x, y).b >= 0.3 && image3.pixel(x, y).b <= 0.4)
         {
            int choixT1[] = {16};  // Vos choix
            int taille = sizeof(choixT1) / sizeof(choixT1[0]);  // Nombre de choix
            int index = std::rand() % taille;  // Génère un index aléatoire
            indicesTexture[x][y] = choixT1[index]; 
         }
        

          if (image3.pixel(x, y).r == 1 && image3.pixel(x,y).g == 0 && image3.pixel(x, y).b == 1)
         {
            int choixT1[] = {20, 21, 22};  // Vos choix
            int taille = sizeof(choixT1) / sizeof(choixT1[0]);  // Nombre de choix
            int index = std::rand() % taille;  // Génère un index aléatoire
            indicesTexture[x][y] = choixT1[index]; 
         }

        // Faites de même pour les autres conditions si nécessaire
    }
}

return indicesTexture;
}





void DessinCarte (GLuint* tab, sil::Image image3,std::vector<std::vector<int>> indicesTexture )
{


// Utilisez les indices de texture stockés lors du dessin
for (int y = 0; y < image3.height(); y++) {
    for (int x = 0; x < image3.width(); x++) {
        glBindTexture(GL_TEXTURE_2D, tab[indicesTexture[x][y]]);
        
          glPushMatrix();

             glRotatef(180., 0., 0., 1.);
           

            glColor3f(1.0,1.0,1.0);
                
               
		        glBegin(GL_QUADS);
		        glTexCoord2f(0, 0);
		        glVertex3f( 8 - x,8 - y,0);
		        glTexCoord2f(1, 0);
		        glVertex3f( 7 - x,8 - y,0);
		        glTexCoord2f(1, 1);
		        glVertex3f( 7 - x,7 - y,0);
		        glTexCoord2f(0, 1);
		        glVertex3f( 8 - x,7 - y,0);
		        glEnd();
                glPopMatrix();

            glBindTexture(GL_TEXTURE_2D, 0);
    }
}


    
}
