#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <cmath>
#include <vector>
#include "dessinerCarte.hpp"
#include "loadSpriteCarte.hpp"
#include <sil/sil.hpp>


#include <GL/gl.h>
#include <math.h> 
#include <cmath> 
#include <iomanip>


#include "graphe.hpp"
#include "ValiditeITD.hpp"
#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <stack>
#include <queue>

#include "tours.hpp"
#include "ennemis.hpp"
#include "jeu.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "3D_tools.hpp"
#include "draw_scene.hpp"

#include "jeu.hpp"



/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "TD05";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* IHM flag */
static int flag_filaire = 0;
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

void onWindowResized(GLFWwindow* /* window */, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspective(60.0,aspectRatio,Z_NEAR,Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow* window, int key, int /* scancode */, int action, int /* mods */)
{
	int is_pressed = (action == GLFW_PRESS); 
	switch(key) {
		case GLFW_KEY_A :
		case GLFW_KEY_ESCAPE :
			if (is_pressed) glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_F :
			if (is_pressed) {
				flag_filaire = !flag_filaire;
				std::cout <<"Mode filaire : "<<((flag_filaire)?"ON":"OFF")<<std::endl;
			}
			break;
		case GLFW_KEY_R :
			if (is_pressed) flag_animate_rot_arm = 1-flag_animate_rot_arm;
			break;
		case GLFW_KEY_T :
			if (is_pressed) flag_animate_rot_scale = 1-flag_animate_rot_scale;
			break;
		case GLFW_KEY_J :
			if(dist_zoom<60.0f) dist_zoom*=1.1;
			std::cout<<"Zoom is "<<dist_zoom<<std::endl;
			break;
		case GLFW_KEY_I :
			if(dist_zoom>1.0f) dist_zoom*=0.9;
			std::cout<<"Zoom is "<<dist_zoom<<std::endl;
			break;
		case GLFW_KEY_UP :
			if (phy>2) phy -= 2;
			std::cout<<"Phy : "<<phy<<std::endl;
			break;
		case GLFW_KEY_DOWN :
			if (phy<=88.) phy += 2;
			std::cout<<"Phy : "<<phy<<std::endl;
			break;
		case GLFW_KEY_LEFT :
			theta -= 5;
			break;
		case GLFW_KEY_RIGHT :
			theta += 5;
			break;
		default: std::cout<<"Touche non gérée"<<std::endl;
	}
}

int main(int /* argc */, char** /* argv */)
{
	/* GLFW initialisation */
	GLFWwindow* window;
	  if (!glfwInit()) {
        std::cerr << "Erreur lors de l'initialisation de GLFW" << std::endl;
        return -1;
    }

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		std::cerr << "Erreur lors de la création de la fenêtre GLFW" << std::endl;
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Erreur lors de l'initialisation de GLAD" << std::endl;
		return -1;
	}

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float rotation = 0.0;

	phy = 360;
	theta = 270;
	dist_zoom = 13.8;
	int hauteuraffichage = 0;
	int indicateurVague = 0;



	
	float intervalleApparitionType1 = 0.015;
	float intervalleApparitionType2 = 0.055; // Intervalle de 1 seconde entre chaque apparition
	float tempsEcouleDepuisDerniereApparition = 0.5f;
	

	std::ifstream fichier ("../../data/level2.itd");
   	testValiditeITD (fichier);
	GLuint* tab = chargerTousLesSpritesCartes ();
	GLuint* tab2 = chargerTousLesSpritesJeu();
	if (!tab) {
        std::cerr << "Erreur lors du chargement des textures" << std::endl;
        return -1;
    }
	fichier.close();
	 
	std::ifstream fichier2("../../data/level2.itd");
    if (!fichier2.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier ITD." << std::endl;
        return 1;
    }

	Graph::WeightedGraph graph;
	Jeu::graph = &graph;
    graph.creerNoeudEtArreteGrapheAPartirDeItd(fichier2);
    fichier2.close();
	graph.printGraph();
	bool partieEnCours = true;
	Jeu::partieEnCours = partieEnCours;

	int idPremierNoeud = 0; // Remplacez par l'ID de votre nœud de départ
    int idDernierNoeud = 29; // Remplacez par l'ID de votre nœud d'arrivée
	Jeu::idDernierNoeud = idDernierNoeud;


	std::vector<int> cheminLePlusCourt = graph.dijkstra(idPremierNoeud, idDernierNoeud);

	for (int node_id : cheminLePlusCourt) {
        // std::cout << node_id << " ";
    }

		// Création d'une tour fixe (pour tester)
	Tour tour1;
	tour1.puissance = 10;
	tour1.portee = 5; // Portée en distance de Chebyshev
	tour1.cadence = 1.0f; // Cadence de tir en dixièmes de seconde
	tour1.type = TypeTour::TypeA;
	tour1.posX = 2; // Position X de la tour sur la carte
	tour1.posY = 3; // Position Y de la tour sur la carte
	std::vector<Tour> tours = {tour1};

	std::vector<Ennemi> vague1 = creerEnnemis(5, Type1, &graph, cheminLePlusCourt);
	std::vector<Ennemi> vague2 = creerEnnemis(10, Type2, &graph, cheminLePlusCourt);
	std::vector<Ennemi> vague3 = creerEnnemis(15, Type2, &graph, cheminLePlusCourt);
	



	Jeu::vaguesEnnemis.push_back(vague1);
	Jeu::vaguesEnnemis.push_back(vague2);
	Jeu::vaguesEnnemis.push_back(vague3);


	
	std::ifstream fichier3 ("../../data/level2.itd");
	std::string nomMap = recuperationNomFichierMap(fichier3);
	sil::Image image3{"images/" + nomMap };

	std::vector<std::vector<int>> indicesTextures = scanCartePourTexture (tab,image3);



	while (!glfwWindowShouldClose(window))
	{
		


		// std::cout << Jeu::tempsDepuisFinVague << std::endl;

		if (Jeu::tempsDepuisFinVague >= 0.1f && Jeu::partieEnCours) {
		commencerNouvelleVague();
		Jeu::tempsDepuisFinVague = 0.0f;  // Réinitialisez le temps depuis la fin de la vague
		}
	

    


		double startTime = glfwGetTime();

		glClearColor(0.0,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();
		glEnable(GL_TEXTURE_2D);

		drawFrame();
		DessinCarte(tab, image3, indicesTextures);

		double currentTime = glfwGetTime();
		float dt = static_cast<float>(currentTime - startTime);

		if (tousEnnemisMorts(Jeu::vaguesEnnemis[Jeu::vagueActuelle])) {
    	finVague(true);  // Le joueur a gagné la vague
		Jeu::tempsDepuisFinVague += dt;
    	// break;
    	}
	

		// Logique d'apparition des ennemis
		
		// std::cout << tempsEcouleDepuisDerniereApparition << std::endl;

		if (Jeu::vaguesEnnemis[Jeu::vagueActuelle][indicateurVague].type == Type1) { 
		if (Jeu::prochainEnnemiAAfficher < Jeu::vaguesEnnemis[Jeu::vagueActuelle].size() && tempsEcouleDepuisDerniereApparition >= intervalleApparitionType1) {
        tempsEcouleDepuisDerniereApparition = 0.0f;
        Jeu::prochainEnnemiAAfficher++;
        std::cout << "prochain ennemi à afficher" << Jeu::prochainEnnemiAAfficher << std::endl;
    	}
		}


		if (Jeu::vaguesEnnemis[Jeu::vagueActuelle][indicateurVague].type == Type2) { 
		if (Jeu::prochainEnnemiAAfficher < Jeu::vaguesEnnemis[Jeu::vagueActuelle].size() && tempsEcouleDepuisDerniereApparition >= intervalleApparitionType2) {
        tempsEcouleDepuisDerniereApparition = 0.0f;
        Jeu::prochainEnnemiAAfficher++;
        std::cout << "prochain ennemi à afficher" << Jeu::prochainEnnemiAAfficher << std::endl;
    	}
		}
		

		// Affichage et mouvement des ennemis
		for (int i = 0; i < Jeu::prochainEnnemiAAfficher; ++i){

		 	Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].pts_de_vie -= 0.0000001;
			
			if (!Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].estMort()) {
        	Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].avancer(dt);

			if (Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].type == Type1) 
			{
			glBindTexture(GL_TEXTURE_2D, tab2[0]);   
			indicateurVague = i;
			} 


			if (Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].type == Type2) 
			{
			glBindTexture(GL_TEXTURE_2D, tab2[2]);   
			indicateurVague = i;
			} 
			glPushMatrix();  // Sauvegarder la matrice de transformation actuelle

			// Déplacer l'origine au centre de l'ennemi
			glTranslatef(Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].positionActuelle.x + 0.5f, Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].positionActuelle.y + 0.5f, 0);

			if (Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].type == Type1)  { 
			// Agrandir l'ennemi
			glScalef(2.1f, 2.1f, 1.0f);  // Ajustez ces valeurs pour changer la taille de l'ennemi
			}

			if (Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].type == Type2)  { 
			// Agrandir l'ennemi
			glScalef(2.9f, 2.9f, 1.0f);  // Ajustez ces valeurs pour changer la taille de l'ennemi
			}

			// Dessiner l'ennemi à l'origine (puisque nous avons déplacé l'origine)
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.5f, -0.5f, 0.001 + i * 0.001);  // Ajoutez un décalage à la coordonnée z en fonction de l'index de l'ennemi
			glTexCoord2f(1, 0);
			glVertex3f(0.5f, -0.5f, 0.001 + i * 0.001);
			glTexCoord2f(1, 1);
			glVertex3f(0.5f, 0.5f, 0.001 + i * 0.001);
			glTexCoord2f(0, 1);
			glVertex3f(-0.5f, 0.5f, 0.001 + i * 0.001);
			glEnd();

			glPopMatrix();  // Restaurer la matrice de transformation originale
			glBindTexture(GL_TEXTURE_2D, 0);
			}
			
		}
		ennemiAtteintFin(Jeu::vaguesEnnemis[Jeu::vagueActuelle], Jeu::graph, Jeu::idDernierNoeud);

		

		// Affichage de la tour fixe
		for (const auto& tour : tours) {
			glBindTexture(GL_TEXTURE_2D, tab2[1]);  // Utiliser la texture de la tour

			glPushMatrix();
			glTranslatef(tour.posX + 0.5f, tour.posY + 0.5f, 0.0f);
			glScalef(2.5f, 2.5f, 1.0f);  // Ajustez la taille de la tour si nécessaire

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.5f, -0.5f, 0.001);  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(0.5f, -0.5f, 0.001);
			glTexCoord2f(1, 1);
			glVertex3f(0.5f, 0.5f, 0.001);
			glTexCoord2f(0, 1);
			glVertex3f(-0.5f, 0.5f, 0.001);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glDisable(GL_TEXTURE_2D);
		glfwSwapBuffers(window);
		glfwPollEvents();

		double endTime = glfwGetTime();
		double elapsedTime = endTime - startTime;

		if(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
		}

		tempsEcouleDepuisDerniereApparition += dt;
		std::cout << dt << std::endl;
		Jeu::total_argentEnFloat += 0.05;
		Jeu::totalArgentInt = static_cast<int>(Jeu::total_argentEnFloat);
		std::cout << "Le joueur ce gros rat a " << Jeu::totalArgentInt << " ecus" << std::endl;
		std::cout << "Pts de vie Joueur " << Jeu::points_de_vieJoueur << std::endl;
	    finPartie();
	}

	glDeleteTextures(4, tab);
	glDeleteTextures(3, tab2);

	glfwTerminate();
	return 0;
}
