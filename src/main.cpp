#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <GL/gl.h>
#include <iostream>
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

int const width = 800;
int const height = 800;
int const NombreDePoints = 200;

const double Pi = 3.141592;


/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
};

static const float GL_VIEW_SIZE = 25.;

static float aspectRatio;
void onWindowResized(GLFWwindow* window,int width,int height)
{
 aspectRatio = width / (float) height;
 glViewport(0, 0, width, height);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 if( aspectRatio > 1)
 {
 glOrtho(
 -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
 -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2., -1.0, 1.0);
 }
 else
 {
 glOrtho(
 -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
 -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio,-1.0,1.0);
 }
};


void glfwSetWindowShouldClose	(	GLFWwindow * 	window,int 	value );

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose	(window,1 );
	}       
};

void  drawOrigin()
{
// origine 
		glBegin(GL_LINES);
		glColor3f(1.0f, 0, 0);
    	glVertex2f(- 0.5f, 0);
    	glVertex2f( 0.5f, 0);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 1, 0);
    	glVertex2f(0,- 0.5f);
    	glVertex2f(0,0.5f);
		glEnd();

};

void drawSquare(int full)
{
	if (full == 0){
		glBegin(GL_LINE_LOOP);
    	glVertex2f(- 0.5f, 0.5f);
    	glVertex2f(0.5f, 0.5f);
		glVertex2f( 0.5f,  -0.5f);
		glVertex2f(- 0.5f, -0.5f);
		glEnd();
	}

	else if (full == 1){
		glBegin(GL_POLYGON);
    	glVertex2f(- 0.5f, 0.5f);
    	glVertex2f(0.5f, 0.5f);
		glVertex2f( 0.5f,  -0.5f);
		glVertex2f(- 0.5f, -0.5f);
		glEnd();
	}
}

void drawCircle(int full)
{
	if (full == 0)
	{
		glBegin(GL_LINE_LOOP);
		for (int i=0;i < NombreDePoints; i++)
		{
		
    	glVertex2f( cos(i*((2*Pi)/NombreDePoints))*0.5,  sin(i*((2*Pi)/NombreDePoints))*0.5);
		
		}
		glEnd();
	}

	else if (full == 1)
	{
		glBegin(GL_POLYGON);
		for (int i=0;i < NombreDePoints; i++)
		{
		
    	glVertex2f( cos(i*((2*Pi)/NombreDePoints))*0.5,  sin(i*((2*Pi)/NombreDePoints))*0.5);
		
		}
		glEnd();
	}

	

};

void drawFirstArm () {
	glPushMatrix();
		glScalef(4, 4, 0);
		drawCircle(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(6, 0, 0);
		glScalef(2, 2, 0);
		drawCircle(1);
		glPopMatrix();

		glBegin(GL_TRIANGLES);
    	glVertex2f( 0.f, 2.f);
    	glVertex2f(6.f, 1.f);
		glVertex2f( 0.f, -2.f);
		glEnd();

		glBegin(GL_TRIANGLES);
    	glVertex2f( 0.f, -2.f);
    	glVertex2f(6.f, 1.f);
		glVertex2f(6.f, -1.f);
		glEnd();
};

void drawRoundedSquare()
{
	glPushMatrix();
	glScalef(1, 0.75, 0);
	drawSquare(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.75, 1, 0);
	drawSquare(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.375, 0.375, 0);
	glScalef(0.25, 0.25, 0);
	drawCircle(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.375, -0.375, 0);
	glScalef(0.25, 0.25, 0);
	drawCircle(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.375, 0.375, 0);
	glScalef(0.25, 0.25, 0);
	drawCircle(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.375, -0.375, 0);
	glScalef(0.25, 0.25, 0);
	drawCircle(1);
	glPopMatrix();

};

void drawSecondArm()
{
glPushMatrix();
drawRoundedSquare();
glPopMatrix();

glPushMatrix();
glTranslatef(2.5, 0, 0);
glScalef(4.6, 0.6, 0);
drawSquare(1);
glPopMatrix();

glPushMatrix();
glTranslatef(4.5, 0, 0);
drawRoundedSquare();
glPopMatrix();
}

void drawThirdArm()
{
glPushMatrix();
glScalef(0.6, 0.6, 0);
drawSquare(1);
glPopMatrix();

glPushMatrix();
glTranslatef(4, 0, 0);
glScalef(0.8, 0.8, 0);
drawCircle(1);
glPopMatrix();

glPushMatrix();
glTranslatef(2, 0, 0);
glScalef(4, 0.4, 0);
drawRoundedSquare();
glPopMatrix();
}

	






int main() {

	std::ifstream fichier ("../../data/level1.itd");
   
  testValiditeITD (fichier);
	
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
#ifdef __APPLE__
    // We need to explicitly ask for a 3.3 context on Mac
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow* window = glfwCreateWindow(width, height, "TD 01 Ex 03", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    };


	glfwSetKeyCallback(window, key_callback);




    // Make the window's context current
    glfwMakeContextCurrent(window);

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);
	
	
	onWindowResized(window,width,height);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();



		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

        // render exemple quad
        // glColor3f(1.0f, 0.0f, 0.0f);
        // glBegin(GL_QUADS);
        //     glVertex2f(-0.5f, -0.5f);
        //     glVertex2f(0.5f, -0.5f);
        //     glVertex2f(0.5f, 0.5f);
        //     glVertex2f(-0.5f, 0.5f);
        // glEnd();

		// Je dessine quelques points
		glBegin(GL_POINTS);
		//point blanc
		glColor3f(1.0f, 1.0f, 1.0f);
 		glVertex2f(0, 0);

		// point rouge
		glColor3f(1.0f, 0.0f, 0.0f);
 		glVertex2f(0.5, 0.0);

		// point vert
		glColor3f(0.0f, 1.0f, 0.0f);
 		glVertex2f(0.0, 0.5);


		// point violet
		glColor3f(1.0f, 0.0f, 1.0f);
 		glVertex2f(-0.5, -0.5);
 		// eventuellement d’autres points …
		glEnd();

		
		// drawOrigin();
		
		// drawRoundedSquare();
		glColor3f(1.f, 0.f, 0.f);
		glPushMatrix();
		glRotatef(45, 0., 0., 1.);
		drawFirstArm();
		glPopMatrix();
		
		glColor3f(0.f, 1.f, 0.);
		glPushMatrix();
		glRotatef(45, 0., 0., 1.);
		glTranslatef(6, 0, 0);
		glRotatef(-10, 0., 0., 1.);
		drawSecondArm();
		glPopMatrix();

		// drawSecondArm();
		
		
		
		glColor3f(0.f, 0.f, 1.);
		glPushMatrix();
		glRotatef(45, 0., 0., 1.);
		glTranslatef(6, 0, 0);
		glRotatef(-10, 0., 0., 1.);
		glTranslatef(4.5, 0, 0);
		glRotatef(35, 0., 0., 1.);
		drawThirdArm();
		glPopMatrix();


		// glRotatef(45, 0., 0., 1.);
		// glTranslatef(1, 0, 0);
		// glColor3f(1.f, 0.f, 0.);
		// drawSquare();
		// glLoadIdentity();


		// glTranslatef(1, 0, 0);
		// glRotatef(45, 0., 0., 1.);
		// glColor3f(0.33f, 0.f, 1.f);
		// drawSquare();
		
		

	
        
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
	}

    return 0;
}

