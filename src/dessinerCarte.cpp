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



std::string recuperationNomFichierMap (std::ifstream& fichier) {
    // On définit l'odre attendu des lignes
    std::vector<std::string> ordreAttendu = {"ITD","map"};
    
    // on va lire et stocker le contenu des lignes du fichier
    std::string contenuLigne {};
    int ligneActuelle {};

    // Variable pour suivre si une erreur a été trouvée
    
    std::string nomMap ="";
    
   
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

     
        if (PremierMotaComparer == "map")
        {
            nomMap =DecoupageMot[1];
    
        }
        // on passe à la ligne d'après
        ligneActuelle += 1;
    }
    return nomMap;
}


void DessinCarte (GLuint* tab)
{
    glBindTexture(GL_TEXTURE_2D, tab[0]);

		
		
		
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f( -2,2,0);
		glTexCoord2f(1, 0);
		glVertex3f( 2,2,0);
		glTexCoord2f(1, 1);
		glVertex3f( 2,-2,0);
		glTexCoord2f(0, 1);
		glVertex3f( -2,-2,0);
		glEnd();
		
		
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindTexture(GL_TEXTURE_2D, tab[1]);

		
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f( 2,2,0);
		glTexCoord2f(1, 0);
		glVertex3f( 6,2,0);
		glTexCoord2f(1, 1);
		glVertex3f( 6,-2,0);
		glTexCoord2f(0, 1);
		glVertex3f( 2,-2,0);
		glEnd();
		
		
		glBindTexture(GL_TEXTURE_2D, 0);













    

    // for (int x{0}; x < image.width(); x++)
    // {
    // for (int y{0}; y < image.height(); y++)
    
    //     {
            
    //         if (image.pixel(x, y).r == 0 && image.pixel(x,y).g == 0 && image.pixel(x, y).b == 1)
    //         {
	// 	        glBindTexture(GL_TEXTURE_2D, tab[0]);		        
    //         }

    //         else if (image.pixel(x, y).r == 1 && image.pixel(x,y).g == 0 && image.pixel(x, y).b == 0)
    //         {
    //             glBindTexture(GL_TEXTURE_2D, tab[1]);
    //         }

    //          else if (image.pixel(x, y).r == 0 && image.pixel(x,y).g == 0 && image.pixel(x, y).b == 0)
    //         {
    //             glBindTexture(GL_TEXTURE_2D, tab[2]);
    //         }
    //           else if (image.pixel(x, y).r == 1 && image.pixel(x,y).g == 1 && image.pixel(x, y).b == 1)
    //         {
    //             glBindTexture(GL_TEXTURE_2D, tab[3]);
    //         }
            
    //         glColor3f(1.0,1.0,1.0);
	// 	        glBegin(GL_QUADS);
	// 	        glTexCoord2f(0, 0);
	// 	        glVertex3f( -4 + x,4 - y,0);
	// 	        glTexCoord2f(1, 0);
	// 	        glVertex3f( -3 + x,4 - y,0);
	// 	        glTexCoord2f(1, 1);
	// 	        glVertex3f( -3 + x,3 - y,0);
	// 	        glTexCoord2f(0, 1);
	// 	        glVertex3f( -4 + x,3 - y,0);
	// 	        glEnd();

    //         glBindTexture(GL_TEXTURE_2D, 0);
    //     }
    // }
    
}
