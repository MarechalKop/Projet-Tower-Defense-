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




void DessinCarte (GLuint* tab, sil::Image image3)
{
    // glBindTexture(GL_TEXTURE_2D, tab[0]);

		
		
		
	// 	glColor3f(1.0,1.0,1.0);
	// 	glBegin(GL_QUADS);
	// 	glTexCoord2f(0, 0);
	// 	glVertex3f( -2,2,0);
	// 	glTexCoord2f(1, 0);
	// 	glVertex3f( 2,2,0);
	// 	glTexCoord2f(1, 1);
	// 	glVertex3f( 2,-2,0);
	// 	glTexCoord2f(0, 1);
	// 	glVertex3f( -2,-2,0);
	// 	glEnd();
		
		
	// 	glBindTexture(GL_TEXTURE_2D, 0);

	// 	glBindTexture(GL_TEXTURE_2D, tab[1]);

		
	// 	glColor3f(1.0,1.0,1.0);
	// 	glBegin(GL_QUADS);
	// 	glTexCoord2f(0, 0);
	// 	glVertex3f( 2,2,0);
	// 	glTexCoord2f(1, 0);
	// 	glVertex3f( 6,2,0);
	// 	glTexCoord2f(1, 1);
	// 	glVertex3f( 6,-2,0);
	// 	glTexCoord2f(0, 1);
	// 	glVertex3f( 2,-2,0);
	// 	glEnd();
		
		
	// 	glBindTexture(GL_TEXTURE_2D, 0);




    for (int x{0}; x < image3.width(); x++)
    {
    for (int y{0}; y < image3.height(); y++)
    
        {
            
            if (image3.pixel(x, y).r == 0 && image3.pixel(x,y).g == 0 && image3.pixel(x, y).b == 1)
            {
		        glBindTexture(GL_TEXTURE_2D, tab[0]);		        
            }

            else if (image3.pixel(x, y).r == 1 && image3.pixel(x,y).g == 0 && image3.pixel(x, y).b == 0)
            {
                glBindTexture(GL_TEXTURE_2D, tab[1]);
            }

             else if (image3.pixel(x, y).r >= 0 && image3.pixel(x, y).r <= 0.1 && image3.pixel(x, y).g >= 0 && image3.pixel(x, y).g <= 0.1 && image3.pixel(x, y).b >= 0 && image3.pixel(x, y).b <= 0.1)
            {
                glBindTexture(GL_TEXTURE_2D, tab[2]);
            }
              else if (image3.pixel(x, y).r >= 0.98 && image3.pixel(x, y).r <= 1 && image3.pixel(x, y).g >= 0.98 && image3.pixel(x, y).g <= 1 && image3.pixel(x, y).b >= 0.98 && image3.pixel(x, y).b <= 1)
            {
                glBindTexture(GL_TEXTURE_2D, tab[3]);
            }

            // else 
            // {
            //      glBindTexture(GL_TEXTURE_2D, tab[3]);
            // }
            
            glColor3f(1.0,1.0,1.0);
		        glBegin(GL_QUADS);
		        glTexCoord2f(0, 0);
		        glVertex3f( -4 + x,4 - y,0);
		        glTexCoord2f(1, 0);
		        glVertex3f( -3 + x,4 - y,0);
		        glTexCoord2f(1, 1);
		        glVertex3f( -3 + x,3 - y,0);
		        glTexCoord2f(0, 1);
		        glVertex3f( -4 + x,3 - y,0);
		        glEnd();

            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
    
}
