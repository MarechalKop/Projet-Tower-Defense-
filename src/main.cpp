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
	if (!glfwInit()) return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

	float rotation = 0.0;

	phy = 360;
	 theta = 270;
	dist_zoom = 7;

	
	std::ifstream fichier ("../../data/level1.itd");
   	testValiditeITD (fichier);
	GLuint* tab = chargerTousLesSprites ();
	fichier.close();
	 

	std::ifstream fichier2("../../data/level1.itd");
    if (!fichier2.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier ITD." << std::endl;
        return 1;
    }

	Graph::WeightedGraph graph;
    graph.creerNoeudEtArreteGrapheAPartirDeItd(fichier2);
    fichier2.close();
	graph.printGraph();

	int idPremierNoeud = 0; // Remplacez par l'ID de votre nœud de départ
    int idDernierNoeud = 7; // Remplacez par l'ID de votre nœud d'arrivée

	std::vector<int> cheminLePlusCourt = graph.dijkstra(idPremierNoeud, idDernierNoeud);

	// std::cout << "Le chemin le plus court de " << idPremierNoeud << " a " << idDernierNoeud<< " est : ";
    for (int node_id : cheminLePlusCourt) {
        // std::cout << node_id << " ";
    }
    // std::cout << std::endl;


	Ennemi ennemi;
	// Initialisez votre ennemi...
	ennemi.pts_de_vie = 100; // Par exemple
	ennemi.vitesse = 100; // Par exemple
	ennemi.recompense = 10; // Par exemple
	ennemi.couleur = "rouge"; // Par exemple
	ennemi.type = TypeEnnemi::Type1; // Par exemple
	ennemi.graphe = &graph;

	if (!cheminLePlusCourt.empty()) {
    ennemi.positionActuelle = graph.getNodePosition(cheminLePlusCourt[0]);
    if (cheminLePlusCourt.size() > 1) {
        ennemi.positionProchaine = graph.getNodePosition(cheminLePlusCourt[1]);
    } else {
        ennemi.positionProchaine = ennemi.positionActuelle;
    }
    ennemi.setChemin(cheminLePlusCourt);
    ennemi.chercherProchainePosition(); // Initialiser la prochaine position
}
	
	
	
	std::ifstream fichier3 ("../../data/level1.itd");
	std::string nomMap = recuperationNomFichierMap(fichier3);
	sil::Image image3{"images/" + nomMap };

		
		
		//////////////////////////////////

		

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		/* Scene rendering */
		glEnable(GL_TEXTURE_2D);
		
		 
		
		// glBindTexture(GL_TEXTURE_2D, 0);
		
		drawFrame();
		// std::cout << "Position de l'ennemi : (" << ennemi.positionActuelle.x << ", " << ennemi.positionActuelle.y << ")\n";
		// std::cout << "Prochaine position : (" << ennemi.positionProchaine.x << ", " << ennemi.positionProchaine.y << ")\n";
		DessinCarte (tab, image3);

		glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(ennemi.positionActuelle.x, ennemi.positionActuelle.y, 0.001);
    glTexCoord2f(1, 0);
    glVertex3f(ennemi.positionActuelle.x + 1, ennemi.positionActuelle.y, 0.001);
    glTexCoord2f(1, 1);
    glVertex3f(ennemi.positionActuelle.x + 1, ennemi.positionActuelle.y + 1, 0.001);
    glTexCoord2f(0, 1);
    glVertex3f(ennemi.positionActuelle.x , ennemi.positionActuelle.y + 1, 0.001);
    glEnd();

		glDisable(GL_TEXTURE_2D);


		/* Initial scenery setup */

		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}


		float dt = static_cast<float>(elapsedTime);
    	// std::cout << "Elapsed time (dt): " << dt << std::endl;
    	// std::cout << "Ennemi speed: " << ennemi.vitesse << std::endl;
    	ennemi.avancer(dt);


		/* Animate scenery */
		rotation++;
	}

	glDeleteTextures(4, tab);


	glfwTerminate();
	return 0;
}


