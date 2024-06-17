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
#include <utility>



/* Window properties */
static const unsigned int WINDOW_WIDTH = 2000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "L'attaque des fardadets malicieux à MocheVille";
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

int typeTourSelectionnee = -1; // -1 indique qu'aucune tour n'est sélectionnée
	bool placementTour = false;

	static int posXTourEnAttente; // Ajout d'une tour en attente
	static int posYTourEnAttente;

	
	static bool TourPeutEtrePlaceeIci = false;
	std::vector<Tour> tours;
	std::vector<std::pair<int,int>> TableauNouvellesCasesInterdites;

	bool JeuACommence = false; 

    

void onKey(GLFWwindow* window, int key, int /* scancode */, int action, int /* mods */)
{
	int is_pressed = (action == GLFW_PRESS); 
	switch(key) {
		case GLFW_KEY_Q : 
			if (is_pressed && Jeu::totalArgentInt >= 100 && placementTour == false && JeuACommence == true)
			{
				typeTourSelectionnee = 1; // Tour de type A
            	std::cout << "Tour A sélectionnée" << std::endl;
				posXTourEnAttente = 0;
				posYTourEnAttente = 0;
				Jeu::total_argentEnFloat -= 100;
				placementTour = true;
			}
			else if (is_pressed && placementTour == true && TourPeutEtrePlaceeIci == true && typeTourSelectionnee == 1)
			{
			
				Tour tourA = creerTour(TypeTour::TypeA, posXTourEnAttente, posYTourEnAttente);
				tours.push_back(tourA);
				TableauNouvellesCasesInterdites.push_back(std::make_pair(posXTourEnAttente,posYTourEnAttente));
				
				placementTour = false;
				typeTourSelectionnee = -1;
			}
			break; 
		// comment ça c'est en qwerty?
		// case GLFW_KEY_V :
			
        //     break;
		case GLFW_KEY_W :
			if (is_pressed && Jeu::totalArgentInt >= 200 && placementTour == false  && JeuACommence == true)
			{
			typeTourSelectionnee = 2; // Tour de type B
            std::cout << "Tour B sélectionnée" << std::endl;
			std::cout << "Tour A sélectionnée" << std::endl;
			posXTourEnAttente = 0;
			posYTourEnAttente = 0;
			Jeu::total_argentEnFloat -= 200;
			placementTour = true;
			}
			else if (is_pressed && placementTour == true && TourPeutEtrePlaceeIci == true && typeTourSelectionnee == 2)
			{
				
				
				Tour tourA = creerTour(TypeTour::TypeB, posXTourEnAttente, posYTourEnAttente);
				tours.push_back(tourA);
				TableauNouvellesCasesInterdites.push_back(std::make_pair(posXTourEnAttente,posYTourEnAttente));
				
				placementTour = false;
				typeTourSelectionnee = -1;
			}
            break;

			  case GLFW_KEY_P : 
            if (is_pressed && JeuACommence == false) {
                JeuACommence = true;  // Basculez la valeur de isPaused lorsque 'p' est pressé
            }
            break; 



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
		// case GLFW_KEY_R :
		// 	if (is_pressed) flag_animate_rot_arm = 1-flag_animate_rot_arm;
		// 	break;
		// case GLFW_KEY_T :
		// 	if (is_pressed) flag_animate_rot_scale = 1-flag_animate_rot_scale;
		// 	break;
		// case GLFW_KEY_J :
		// 	if(dist_zoom<60.0f) dist_zoom*=1.1;
		// 	std::cout<<"Zoom is "<<dist_zoom<<std::endl;
		// 	break;
		// case GLFW_KEY_I :
		// 	if(dist_zoom>1.0f) dist_zoom*=0.9;
		// 	std::cout<<"Zoom is "<<dist_zoom<<std::endl;
		// 	break;
		case GLFW_KEY_UP :
			if (is_pressed && placementTour && posYTourEnAttente < 7) {
			posYTourEnAttente ++;
			}
			break;
		case GLFW_KEY_DOWN :
			if (is_pressed && placementTour && posYTourEnAttente >= -7) {
			posYTourEnAttente --;
			}
			break;
		case GLFW_KEY_LEFT :
			if (is_pressed && placementTour && posXTourEnAttente > -7) {
			posXTourEnAttente --;
			}
			break;
		case GLFW_KEY_RIGHT :
			if (is_pressed && placementTour && posXTourEnAttente < 7 ) {
			posXTourEnAttente ++;
			}
		default: std::cout<<"Touche non gérée"<<std::endl;
	}
}


int main(int /* argc */, char** /* argv */)
{

	// Ajouter des éléments au vecteur
	std::vector<std::pair<int,int>> PeutOnPlacerTourIci = CreationVectorPeutOnPlacerTourIci();

	for (int i{}; i < PeutOnPlacerTourIci.size(); i++)
	{
		std::cout << "Coordonee autorisee (" << PeutOnPlacerTourIci[i].first << " ; " << PeutOnPlacerTourIci[i].second << ")" << std::endl;
	}


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
	int indiceZ = 1;
	bool EnnemiArriveFin = false;
	int nombreSegment = 100;
	int rayon {};



	
	float intervalleApparitionType1 = 0.015;
	float intervalleApparitionType2 = 0.055; // Intervalle de 1 seconde entre chaque apparition
	float tempsEcouleDepuisDerniereApparition = 0.5f;
	

	std::ifstream fichier ("../../data/level2.itd");
   	testValiditeITD (fichier);
	GLuint* tab = chargerTousLesSpritesCartes ();
	GLuint* tab2 = chargerTousLesSpritesJeu();
	GLuint* tab3 = chargerTousLesSpritesChiffre();
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


	Tour tourA = creerTour(TypeTour::TypeA, -1, 3);
	Tour tourB = creerTour(TypeTour::TypeB, 5, -2);
	
	

	
	
	
	std::vector<Ennemi> vague1 = creerEnnemis(10, Type1, &graph, cheminLePlusCourt);
	std::vector<Ennemi> vague2 = creerEnnemis(10, Type2, &graph, cheminLePlusCourt);
	std::vector<Ennemi> vague3 = creerEnnemis(20, Type2, &graph, cheminLePlusCourt);
	
	std::vector<Projectile> projectiles;



	Jeu::vaguesEnnemis.push_back(vague1);
	Jeu::vaguesEnnemis.push_back(vague2);
	Jeu::vaguesEnnemis.push_back(vague3);


	
	std::ifstream fichier3 ("../../data/level2.itd");
	std::string nomMap = recuperationNomFichierMap(fichier3);
	sil::Image image3{"images/" + nomMap };

	std::vector<std::vector<int>> indicesTextures = scanCartePourTexture (tab,image3);



	while (!glfwWindowShouldClose(window))
	{

		 // Vérifiez si le jeu est en pause avant de mettre à jour le jeu
        // Mettez à jour la logique du jeu ici
    
		if (Jeu::total_argentEnFloat >= 999)
		{
		
			Jeu::total_argentEnFloat = 999;

			
		}

		std::cout << "Contenu du tableau des cases interdites : " << std::endl;
		for (int i{}; i < TableauNouvellesCasesInterdites.size(); i++)
		{
			std::cout << "( " << TableauNouvellesCasesInterdites[i].first << " " << TableauNouvellesCasesInterdites[i].second << " )" << std::endl;
		}
		
		// std::cout << Jeu::tempsDepuisFinVague << std::endl;

		if (Jeu::tempsDepuisFinVague >= 0.05f && Jeu::partieEnCours) {
		commencerNouvelleVague();
		Jeu::tempsDepuisFinVague = 0.0f;  // Réinitialisez le temps depuis la fin de la vague
		}
	

		double startTime = glfwGetTime();

		glClearColor(0.6509,0.6901,0.3098,0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();
		glEnable(GL_TEXTURE_2D);

		drawFrame();
		glPushMatrix();
		glTranslatef(-6,0, 0);
		DessinCarte(tab, image3, indicesTextures);
		glPopMatrix();

		double currentTime = glfwGetTime();
		float dt = static_cast<float>(currentTime - startTime);

		std::cout << "placement tour est " << placementTour << std::endl;

		glPushMatrix();
		glTranslatef(-6,0, 0);
		
		if (placementTour == true)
		{
			TourPeutEtrePlaceeIci = false;
		

			if (typeTourSelectionnee == 1){
			
			glBindTexture(GL_TEXTURE_2D, tab2[1]); 
			
			glPushMatrix();  // Sauvegarder la matrice de transformation actuelle

			
			glTranslatef(posXTourEnAttente - 0.5f, posYTourEnAttente, 0);
			glScalef(2.f, 2.f, 1.0f);
			std::cout << "la tour en attente se trouve en " << "( " << posXTourEnAttente << " ; " << posYTourEnAttente << " )" << std::endl;
			for (int i {}; i < PeutOnPlacerTourIci.size(); i++)
			{
    		if (posXTourEnAttente == PeutOnPlacerTourIci[i].first && posYTourEnAttente == PeutOnPlacerTourIci[i].second )
    		{
        		TourPeutEtrePlaceeIci = true;
        		for (int j{}; j < TableauNouvellesCasesInterdites.size(); j++)
        		{
           		 if (posXTourEnAttente == TableauNouvellesCasesInterdites[j].first && posYTourEnAttente == TableauNouvellesCasesInterdites[j].second )
           		 {
                TourPeutEtrePlaceeIci = false;
                break;  // Arrête la vérification une fois que vous avez trouvé une correspondance
            		}
        			}
        		if (!TourPeutEtrePlaceeIci) {
            		break;  // Si TourPeutEtrePlaceeIci est false, arrêtez également la boucle externe
        		}
    			}
			}
			
			std::cout << "La tour est bien placé : " << TourPeutEtrePlaceeIci << std::endl;

			
			rayon = 4;
			glLineWidth(3.0f);

			// Dessiner l'ennemi à l'origine (puisque nous avons déplacé l'origine)
			glBegin(GL_QUADS);
			if (TourPeutEtrePlaceeIci == true)
			{
				glColor3f(0.0,1.0,0.0);
				
			}
			else if (TourPeutEtrePlaceeIci == false)
			{
				glColor3f(1.0,0.0,0.0);
				
			}
			
			glTexCoord2f(0, 0);
			glTexCoord2f(0, 0);
			glVertex3f(0.f, 0.f, 0.0005 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(1.f, 0.f, 0.0005);
			glTexCoord2f(1, 1);
			glVertex3f(1.f, 1.2f, 0.0005);
			glTexCoord2f(0, 1);
			glVertex3f(0.f, 1.2f,0.0005);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);
			glPopMatrix();

			

			}

			if (typeTourSelectionnee == 2){

			glBindTexture(GL_TEXTURE_2D, tab2[3]); 
			
			glPushMatrix();  // Sauvegarder la matrice de transformation actuelle

			// Déplacer l'origine au centre de l'ennemi
			glTranslatef(posXTourEnAttente - 0.5f, posYTourEnAttente, 0);
			glScalef(2.f, 2.f, 1.0f);
			std::cout << "la tour en attente se trouve en " << "( " << posXTourEnAttente << " ; " << posYTourEnAttente << " )" << std::endl;
			for (int i {}; i < PeutOnPlacerTourIci.size(); i++)
			{
    		if (posXTourEnAttente == PeutOnPlacerTourIci[i].first && posYTourEnAttente == PeutOnPlacerTourIci[i].second )
    		{
        		TourPeutEtrePlaceeIci = true;
        		for (int j{}; j < TableauNouvellesCasesInterdites.size(); j++)
        		{
           		 if (posXTourEnAttente == TableauNouvellesCasesInterdites[j].first && posYTourEnAttente == TableauNouvellesCasesInterdites[j].second )
           		 {
                TourPeutEtrePlaceeIci = false;
                break;  // Arrête la vérification une fois que vous avez trouvé une correspondance
            		}
        			}
        		if (!TourPeutEtrePlaceeIci) {
            		break;  // Si TourPeutEtrePlaceeIci est false, arrêtez également la boucle externe
        		}
    			}
			}

			
			std::cout << "La tour est bien placé : " << TourPeutEtrePlaceeIci << std::endl;

			
			rayon = 6;
			glLineWidth(3.0f);

			// Dessiner l'ennemi à l'origine (puisque nous avons déplacé l'origine)
			glBegin(GL_QUADS);
			if (TourPeutEtrePlaceeIci == true)
			{
				glColor3f(0.0,1.0,0.0);
				
			}
			else if (TourPeutEtrePlaceeIci == false)
			{
				glColor3f(1.0,0.0,0.0);
				
			}
			
			glTexCoord2f(0, 0);
			glTexCoord2f(0, 0);
			glVertex3f(0.f, 0.f, 0.0005 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(1.f, 0.f, 0.0005);
			glTexCoord2f(1, 1);
			glVertex3f(1.f, 1.5f, 0.0005);
			glTexCoord2f(0, 1);
			glVertex3f(0.f, 1.5f, 0.0005);
			glEnd();
			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, 0);
			}







		}
		glPopMatrix();
		glColor3f(1.0,1.0,1.0);
	

		// Logique d'apparition des ennemis
		
		// std::cout << tempsEcouleDepuisDerniereApparition << std::endl;

		if (Jeu::vaguesEnnemis[Jeu::vagueActuelle][indicateurVague].type == Type1) { 
		if (Jeu::prochainEnnemiAAfficher < Jeu::vaguesEnnemis[Jeu::vagueActuelle].size() && tempsEcouleDepuisDerniereApparition >= intervalleApparitionType1) {
        tempsEcouleDepuisDerniereApparition = 0.0f;
        Jeu::prochainEnnemiAAfficher++;
        std::cout << "prochain ennemi a afficher" << Jeu::prochainEnnemiAAfficher << std::endl;
    	}
		}


		if (Jeu::vaguesEnnemis[Jeu::vagueActuelle][indicateurVague].type == Type2) { 
		if (Jeu::prochainEnnemiAAfficher < Jeu::vaguesEnnemis[Jeu::vagueActuelle].size() && tempsEcouleDepuisDerniereApparition >= intervalleApparitionType2) {
        tempsEcouleDepuisDerniereApparition = 0.0f;
        Jeu::prochainEnnemiAAfficher++;
        std::cout << "prochain ennemi à afficher" << Jeu::prochainEnnemiAAfficher << std::endl;
    	}
		}

		glPushMatrix();
		glTranslatef(-6,0, 0);
		
		
	
		// Affichage et mouvement des ennemis
		for (int i = 0; i < Jeu::prochainEnnemiAAfficher; ++i){

		 	// Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].pts_de_vie += 100;
			
			
			if (!Jeu::vaguesEnnemis[Jeu::vagueActuelle][i].estMort() && JeuACommence == true) {
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
		bool EnnemiArriveFin = UnennemiALaFin(Jeu::vaguesEnnemis[Jeu::vagueActuelle], Jeu::graph, Jeu::idDernierNoeud);
		std::cout << "Un ennemi est arrive a la fin :" << EnnemiArriveFin << std::endl;
		

		

		

		// Affichage de la tour fixe
		for (const auto& tour : tours) {

				indiceZ +=1;

				mettreAJourTour( tours, Jeu::vaguesEnnemis[Jeu::vagueActuelle],  dt);
			
			if (tour.type== TypeA ) { 
			glBindTexture(GL_TEXTURE_2D, tab2[1]);  // Utiliser la texture de la tour
			glPushMatrix();
			glTranslatef(tour.posX-0.5, tour.posY, 0.0f);
			glScalef(2.f, 2.f, 1.0f);  // Ajustez la taille de la tour si nécessaire

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0.f, 0.f, 0.015 + indiceZ * 0.0001 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(1.f, 0.f, 0.015 + indiceZ * 0.0001);
			glTexCoord2f(1, 1);
			glVertex3f(1.f, 1.2f, 0.015 + indiceZ * 0.0001 );
			glTexCoord2f(0, 1);
			glVertex3f(0.f, 1.2f, 0.015 + indiceZ * 0.0001);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (tour.type == TypeB ) { 
			glBindTexture(GL_TEXTURE_2D, tab2[3]);  // Utiliser la texture de la tour
			glPushMatrix();
			glTranslatef(tour.posX-0.5, tour.posY, 0.0f);
			glScalef(2.f, 2.f, 1.0f);  // Ajustez la taille de la tour si nécessaire

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0.f, 0.f, 0.015 + indiceZ * 0.0001 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(1.f, 0.f, 0.015 + indiceZ * 0.0001 );
			glTexCoord2f(1, 1);
			glVertex3f(1.f, 1.5f, 0.015 + indiceZ * 0.0001 );
			glTexCoord2f(0, 1);
			glVertex3f(0.f, 1.5f, 0.015 + indiceZ * 0.0001);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
			}
			
		}

		

		std::cout << "Nombre de projectiles avant la boucle : " << Jeu::projectiles.size() << std::endl;

		for (auto it = Jeu::projectiles.begin(); it != Jeu::projectiles.end(); /* pas d'incrémentation ici */) {
		std::cout << "Mise a jour du projectile" << std::endl;
    	it->updatePosition(dt);


		it->cible->aTouche = false;

		glBindTexture(GL_TEXTURE_2D, tab2[7]);
		// Dessiner le projectile
		glPushMatrix();  // Sauvegarder la matrice de transformation actuelle

		// Déplacer l'origine au centre du projectile
		glTranslatef(it->PositionX + 0.5f, it->PositionY + 0.5f, 0);

		// Ajuster la taille du projectile si nécessaire
		glScalef(0.3f, 0.3f, 1.0f);  // Ajustez ces valeurs pour changer la taille du projectile

		// Dessiner le projectile à l'origine (puisque nous avons déplacé l'origine)
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-0.5f, -0.5f, 0.2);  // Ajoutez un décalage à la coordonnée z si nécessaire
		glTexCoord2f(1, 0);
		glVertex3f(0.5f, -0.5f, 0.2);
		glTexCoord2f(1, 1);
		glVertex3f(0.5f, 0.5f, 0.2);
		glTexCoord2f(0, 1);
		glVertex3f(-0.5f, 0.5f, 0.2);
		glEnd();

		glPopMatrix();  // Restaurer la matrice de transformation originale
		glBindTexture(GL_TEXTURE_2D, 0);
		

	

		if (it->cibleAtteinte()) {
		it->cible->degatsEnnemi(it->puissance);
		it->cible->aTouche = true;

		// Ajout d'une instruction d'impression
		std::cout << "Projectile a atteint la cible !" << std::endl;

		if (it->cible->estMort() && Jeu::total_argentEnFloat <= 999) {
		
        Jeu::total_argentEnFloat += it->cible->recompense;
		
        std::cout << "Le joueur a gagné " << it->cible->recompense << " ecus" << std::endl;
    	}
		

		it = Jeu::projectiles.erase(it);
		} 
	else {
		++it;
		}

		if (Jeu::total_argentEnFloat >= 999)
		{
		
			Jeu::total_argentEnFloat = 999;
			
			
		}
		
        Jeu::totalArgentInt = static_cast<int>(Jeu::total_argentEnFloat);
		

	}

	glPopMatrix();




		// La partie qui suit a pour but d'afficher les coeurs du joueurs




		for (int i {0}; i < Jeu::points_de_vieJoueur; i++)
			{

			glBindTexture(GL_TEXTURE_2D, tab2[4]);  // Utiliser la texture de la tour

			glPushMatrix();
			glTranslatef(6 + i*2.5  , 5, 1);
			glScalef(1.5f, 1.5f, 1.0f);  // Ajustez la taille de la tour si nécessaire

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.5f, -0.5f, 0.1 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(0.5f, -0.5f, 0.1);
			glTexCoord2f(1, 1);
			glVertex3f(0.5f, 0.5f, 0.1);
			glTexCoord2f(0, 1);
			glVertex3f(-0.5f, 0.5f, 0.1);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
			
			}



		
		

		double endTime = glfwGetTime();
		double elapsedTime = endTime - startTime;

		if(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
		}
		
		tempsEcouleDepuisDerniereApparition += dt;
		std::cout << dt << std::endl;
		if (Jeu::partieEnCours && JeuACommence == true){ 
		Jeu::total_argentEnFloat += 0.05;
		}
		Jeu::totalArgentInt = static_cast<int>(Jeu::total_argentEnFloat);
		std::cout << "Le joueur ce gros rat a " << Jeu::totalArgentInt << " ecus" << std::endl;
		std::cout << "Pts de vie Joueur " << Jeu::points_de_vieJoueur << std::endl;
		std::cout << "Nous sommes a la vague " << Jeu::vagueActuelle + 1 << std::endl;
		std::cout << "Il y a " << Jeu::vaguesEnnemis.size()  << " vagues" << std::endl;
		

		std::string argentStr = std::to_string(Jeu::totalArgentInt);  // Convertir l'argent en chaîne de caractères
		for (int i = 0; i < argentStr.size(); i++)
		{
		int chiffre = argentStr[i] - '0';  // Convertir le caractère en chiffre
		std::cout << chiffre << std::endl;

		glBindTexture(GL_TEXTURE_2D, tab3[chiffre]);  // Utiliser la texture du chiffre
			
			glPushMatrix();
			glTranslatef(6.5 + i*1.5  , 3, 1);
			glScalef(1.f, 1.f, 1.0f); 

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.5f, -0.5f, 0.1 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(0.5f, -0.5f, 0.1);
			glTexCoord2f(1, 1);
			glVertex3f(0.5f, 0.5f, 0.1);
			glTexCoord2f(0, 1);
			glVertex3f(-0.5f, 0.5f, 0.1);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);


			glBindTexture(GL_TEXTURE_2D, tab2[5]);  // Utiliser la texture du chiffre
			
			glPushMatrix();
			glTranslatef(11.2 , 3, 1);
			glScalef(1.f, 1.2f, 1.0f); 

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.5f, -0.5f, 0.1 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(0.5f, -0.5f, 0.1);
			glTexCoord2f(1, 1);
			glVertex3f(0.5f, 0.5f, 0.1);
			glTexCoord2f(0, 1);
			glVertex3f(-0.5f, 0.5f, 0.1);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);

		}
		

		if (tousEnnemisMorts(Jeu::vaguesEnnemis[Jeu::vagueActuelle])) {
    	finVague(true);  // Le joueur a gagné la vague
		Jeu::tempsDepuisFinVague += dt;
		EnnemiArriveFin = false;
    	// break;
    	}

		int prixTourA = 100;
    	int prixTourB = 200;

		std::string prixTourAStr = std::to_string(prixTourA);
    	std::string prixTourBStr = std::to_string(prixTourB);

		bool assezArgentTourA = Jeu::totalArgentInt >= prixTourA;
    	bool assezArgentTourB = Jeu::totalArgentInt >= prixTourB;
		float alphaTourA = assezArgentTourA ? 1.0f : 0.5f;
    	float alphaTourB = assezArgentTourB ? 1.0f : 0.5f;

		// Tour type A
		glBindTexture(GL_TEXTURE_2D, tab2[1]);
		glColor4f(1.0f, 1.0f, 1.0f, alphaTourA);
		glPushMatrix();
		glTranslatef(6, -0.5, 1); // Position de l'image de la tour 1
		glScalef(0.9f, 0.9f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-1.f, -1.25f, 0.1);
		glTexCoord2f(1, 0);
		glVertex3f(1.f, -1.25f, 0.1);
		glTexCoord2f(1, 1);
		glVertex3f(1.f, 1.25f, 0.1);
		glTexCoord2f(0, 1);
		glVertex3f(-1.f, 1.25f, 0.1);
		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		if (typeTourSelectionnee == 1) {
        glColor3f(1.0, 1.0, 0.0); // Couleur jaune pour le contour
        glBegin(GL_LINE_LOOP);
        glVertex3f(5.1f, -1.75f, 0.2); // Coin bas gauche du contour
        glVertex3f(13.0f, -1.75f, 0.2); // Coin bas droit du contour
        glVertex3f(13.0f, 0.75f, 0.2);  // Coin haut droit du contour
        glVertex3f(5.1f, 0.75f, 0.2);  // Coin haut gauche du contour
        glEnd();
    }

		// Affichage du prix de la tour 1
		for (int i = 0; i < prixTourAStr.size(); i++) {
			int chiffre = prixTourAStr[i] - '0';
			glBindTexture(GL_TEXTURE_2D, tab3[chiffre]);
			glColor4f(1.0f, 1.0f, 1.0f, alphaTourA);
			glPushMatrix();
			glTranslatef(8 + i, -0.6, 1); // Position du prix de la tour 1
			glScalef(0.75f, 0.75f, 1.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.5f, -0.5f, 0.1);
			glTexCoord2f(1, 0);
			glVertex3f(0.5f, -0.5f, 0.1);
			glTexCoord2f(1, 1);
			glVertex3f(0.5f, 0.5f, 0.1);
			glTexCoord2f(0, 1);
			glVertex3f(-0.5f, 0.5f, 0.1);
			glEnd();
			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
		}

			glBindTexture(GL_TEXTURE_2D, tab2[5]);
			
			glPushMatrix();
			glTranslatef(11.25, -0.6, 1);
			glScalef(0.75f, 0.77f, 1.0f);

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.5f, -0.5f, 0.1 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(0.5f, -0.5f, 0.1);
			glTexCoord2f(1, 1);
			glVertex3f(0.5f, 0.5f, 0.1);
			glTexCoord2f(0, 1);
			glVertex3f(-0.5f, 0.5f, 0.1);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);

		// Tour type B
		glBindTexture(GL_TEXTURE_2D, tab2[3]);
		glColor4f(1.0f, 1.0f, 1.0f, alphaTourB);
		glPushMatrix();
		glTranslatef(6, -3, 1); // Position de l'image de la tour 2
		glScalef(0.75f, 0.75f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-1.f, -1.5f, 0.1);
		glTexCoord2f(1, 0);
		glVertex3f(1.f, -1.5f, 0.1);
		glTexCoord2f(1, 1);
		glVertex3f(1.f, 1.5f, 0.1);
		glTexCoord2f(0, 1);
		glVertex3f(-1.f, 1.5f, 0.1);
		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		if (typeTourSelectionnee == 2) {
        glColor3f(1.0, 1.0, 0.0); // Couleur jaune pour le contour
        glBegin(GL_LINE_LOOP);
        glVertex3f(5.1f, -4.5f, 0.2); // Coin bas gauche du contour
        glVertex3f(13.0f, -4.5f, 0.2); // Coin bas droit du contour
        glVertex3f(13.0f, -2.0f, 0.2);  // Coin haut droit du contour
        glVertex3f(5.1f, -2.0f, 0.2);  // Coin haut gauche du contour
        glEnd();
    }

		// Affichage du prix de la tour 2
		for (int i = 0; i < prixTourBStr.size(); i++) {
			int chiffre = prixTourBStr[i] - '0';
			glBindTexture(GL_TEXTURE_2D, tab3[chiffre]);
			glColor4f(1.0f, 1.0f, 1.0f, alphaTourB);
			glPushMatrix();
			glTranslatef(8 + i, -3.25, 1); // Position du prix de la tour 2
			glScalef(0.75f, 0.75f, 1.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.5f, -0.5f, 0.1);
			glTexCoord2f(1, 0);
			glVertex3f(0.5f, -0.5f, 0.1);
			glTexCoord2f(1, 1);
			glVertex3f(0.5f, 0.5f, 0.1);
			glTexCoord2f(0, 1);
			glVertex3f(-0.5f, 0.5f, 0.1);
			glEnd();
			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glBindTexture(GL_TEXTURE_2D, tab2[5]);
			
			glPushMatrix();
			glTranslatef(11.25, -3.25, 1);
			glScalef(0.75f, 0.77f, 1.0f);

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.5f, -0.5f, 0.1f);  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(0.5f, -0.5f, 0.1f);
			glTexCoord2f(1, 1);
			glVertex3f(0.5f, 0.5f, 0.1f);
			glTexCoord2f(0, 1);
			glVertex3f(-0.5f, 0.5f, 0.1f);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);

			//Bouton quitter
			glBindTexture(GL_TEXTURE_2D, tab2[6]);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glPushMatrix();
			glTranslatef(8.5f, -6.0f, 1.0f);
			glScalef(1.0f, 1.0f, 1.0f);

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-2.0f, -0.5f, 0.1f );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(2.0f, -0.5f, 0.1f);
			glTexCoord2f(1, 1);
			glVertex3f(2.0f, 0.5f, 0.1f);
			glTexCoord2f(0, 1);
			glVertex3f(-2.0f, 0.5f, 0.1f);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);

			if (Jeu::finDuJeuVictorieuse == 1)
			{
				glBindTexture(GL_TEXTURE_2D, tab2[9]);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glPushMatrix();
			glTranslatef(-2.4f, 0.0f, 8.0f);
			glScalef(1.0f, 1.0f, 1.0f);

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-2.0f, -0.5f, 0.2 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(2.0f, -0.5f, 0.2);
			glTexCoord2f(1, 1);
			glVertex3f(2.0f, 1.f, 0.2);
			glTexCoord2f(0, 1);
			glVertex3f(-2.0f, 1.f, 0.2);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
			}


				if (Jeu::finDuJeuVictorieuse == 2)
			{
				glBindTexture(GL_TEXTURE_2D, tab2[8]);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glPushMatrix();
			glTranslatef(-2.4f, 0.0f, 8.0f);
			glScalef(1.0f, 1.0f, 1.0f);

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-2.0f, -0.5f, 0.2 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(2.0f, -0.5f, 0.2);
			glTexCoord2f(1, 1);
			glVertex3f(2.0f, 1.f, 0.2);
			glTexCoord2f(0, 1);
			glVertex3f(-2.0f, 1.f, 0.2);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
			}

			
				if (JeuACommence == false)
			{
				glBindTexture(GL_TEXTURE_2D, tab2[10]);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glPushMatrix();
			glTranslatef(-2.6f, 0.0f, 8.0f);
			glScalef(1.5f, 1.5f, 1.0f);

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-2.0f, -0.5f, 0.2 );  // Ajustez le décalage z si nécessaire
			glTexCoord2f(1, 0);
			glVertex3f(2.0f, -0.5f, 0.2);
			glTexCoord2f(1, 1);
			glVertex3f(2.0f, 0.5f, 0.2);
			glTexCoord2f(0, 1);
			glVertex3f(-2.0f, 0.5f, 0.2);
			glEnd();

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
			}

				glBindTexture(GL_TEXTURE_2D, tab3[10]);
				glPushMatrix();
				glTranslatef(4, -0.45, 1); // Position de l'image de la tour 2
				glScalef(0.3f, 0.3f, 1.0f);
				glBegin(GL_QUADS);
				glTexCoord2f(0, 0);
				glVertex3f(-1.f, -1.5f, 0.1);
				glTexCoord2f(1, 0);
				glVertex3f(1.f, -1.5f, 0.1);
				glTexCoord2f(1, 1);
				glVertex3f(1.f, 1.5f, 0.1);
				glTexCoord2f(0, 1);
				glVertex3f(-1.f, 1.5f, 0.1);
				glEnd();
				glPopMatrix();
				glBindTexture(GL_TEXTURE_2D, 0);






				glBindTexture(GL_TEXTURE_2D, tab3[11]);
				glPushMatrix();
				glTranslatef(4, -3.1, 1); // Position de l'image de la tour 2
				glScalef(0.3f, 0.3f, 1.0f);
				glBegin(GL_QUADS);
				glTexCoord2f(0, 0);
				glVertex3f(-1.f, -1.5f, 0.1);
				glTexCoord2f(1, 0);
				glVertex3f(1.f, -1.5f, 0.1);
				glTexCoord2f(1, 1);
				glVertex3f(1.f, 1.5f, 0.1);
				glTexCoord2f(0, 1);
				glVertex3f(-1.f, 1.5f, 0.1);
				glEnd();
				glPopMatrix();
				glBindTexture(GL_TEXTURE_2D, 0);














			

			
			

	    finPartie();	


		glfwSwapBuffers(window);
		glfwPollEvents();
		glDisable(GL_TEXTURE_2D);

	
	
	}

	glDeleteTextures(24, tab);
	glDeleteTextures(11, tab2);
	glDeleteTextures(12, tab3);

	glfwTerminate();
	return 0;
}