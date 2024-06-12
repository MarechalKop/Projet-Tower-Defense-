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
	dist_zoom = 13.5;
	int hauteuraffichage = 0;
	
	float intervalleApparition = 0.015; // Intervalle de 1 seconde entre chaque apparition
	float tempsEcouleDepuisDerniereApparition = 0.5f;
	int prochainEnnemiAAfficher = 0;

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
    graph.creerNoeudEtArreteGrapheAPartirDeItd(fichier2);
    fichier2.close();
	graph.printGraph();

	int idPremierNoeud = 0; // Remplacez par l'ID de votre nœud de départ
    int idDernierNoeud = 29; // Remplacez par l'ID de votre nœud d'arrivée

	std::vector<int> cheminLePlusCourt = graph.dijkstra(idPremierNoeud, idDernierNoeud);

	for (int node_id : cheminLePlusCourt) {
        // std::cout << node_id << " ";
    }

	std::vector<Ennemi> ennemisType1 = creerEnnemis(5, Type1, &graph, cheminLePlusCourt);

	std::ifstream fichier3 ("../../data/level2.itd");
	std::string nomMap = recuperationNomFichierMap(fichier3);
	sil::Image image3{"images/" + nomMap };

	 std::vector<std::vector<int>> indicesTextures = scanCartePourTexture (tab,image3);

	while (!glfwWindowShouldClose(window))
	{
		double startTime = glfwGetTime();

		glClearColor(0.2,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();
		glEnable(GL_TEXTURE_2D);

		drawFrame();
		DessinCarte(tab, image3, indicesTextures);

		double currentTime = glfwGetTime();
		float dt = static_cast<float>(currentTime - startTime);

		

		// Logique d'apparition des ennemis
		
		std::cout << tempsEcouleDepuisDerniereApparition << std::endl;

		if (prochainEnnemiAAfficher < ennemisType1.size() && tempsEcouleDepuisDerniereApparition >= intervalleApparition) {
			tempsEcouleDepuisDerniereApparition = 0.0f;
			prochainEnnemiAAfficher++;
			std::cout << "prochain ennemi à afficher" << prochainEnnemiAAfficher << std::endl;
		}

		// Affichage et mouvement des ennemis
		for (int i = 0; i < prochainEnnemiAAfficher; ++i) {
			ennemisType1[i].avancer(dt);
			
			glBindTexture(GL_TEXTURE_2D, tab2[0]);    
			glPushMatrix();  // Sauvegarder la matrice de transformation actuelle

			// Déplacer l'origine au centre de l'ennemi
			glTranslatef(ennemisType1[i].positionActuelle.x + 0.5f, ennemisType1[i].positionActuelle.y + 0.5f, 0);

			// Agrandir l'ennemi
			glScalef(2.1f, 2.1f, 1.0f);  // Ajustez ces valeurs pour changer la taille de l'ennemi

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
	}

	glDeleteTextures(4, tab);
	glDeleteTextures(1, tab2);

	glfwTerminate();
	return 0;
}
