#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <GL/glut.h>

#define MAIN_DEBUG 0
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
using namespace glm;

#include "room.hpp"

vec3 cameraPos = vec3 (0.0f, 0.0f, -1.0f);
vec3 cameraTarget = vec3 (0.0f, 0.0f, 1.0f);
vec3 cameraUp = vec3 (0.0f, 1.0f, 0.0f);

float camSpeed = 0.045f;
float mouseSpeed = 0.0055f;
float horizontalAngle = 3.14f;	   	 // Initial horizontal angle : toward -Z
float verticalAngle = 0.0f;			 // Initial vertical angle : none
float deltaTime;
float planeScale = 10.0f;

GLFWwindow* window;
double windowSizeX = 800, windowSizeY = 600;

RoomNode *rooms = NULL;

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Right vector
	vec3 right = vec3(
			sin(horizontalAngle - 3.14f/2.0f), 
			0,
			cos(horizontalAngle - 3.14f/2.0f)
			);
	switch (key) 
	{
		case GLFW_KEY_W:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos += cameraTarget * deltaTime * camSpeed;
			}
			break;
		case GLFW_KEY_S:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos -= cameraTarget * deltaTime * camSpeed;
			}
			break;
		case GLFW_KEY_D:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos += right * deltaTime * camSpeed;
			}
			break;
		case GLFW_KEY_A:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos -= right * deltaTime * camSpeed;
			}
			break;
	}

#if MAIN_DEBUG
	printf("Right: {%f, %f, %f}\n", right.x, right.y, right.z);
#endif
}

void computeVectorsFromInputs(void)
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Compute new orientation
	horizontalAngle = mouseSpeed * float(windowSizeX/2 - xpos);
	verticalAngle   = mouseSpeed * float( windowSizeY/2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	cameraTarget = vec3(
			cos(verticalAngle) * sin(horizontalAngle), 
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
			);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	vec3 direction = cameraPos + cameraTarget;
	gluLookAt(                       
			cameraPos.x, cameraPos.y, cameraPos.z,              			
			direction.x, direction.y, direction.z,           
			cameraUp.x, cameraUp.y, cameraUp.z                
			);
#if MAIN_DEBUG
	printf("\nCursor position (%f, %f)\n", xpos, ypos);
	printf("H_Angle: %f V_Angle %f\n", horizontalAngle, verticalAngle);
	printf("Camera position: {%f, %f, %f}\n", cameraPos.x, cameraPos.y, cameraPos.z);
	printf("Camera front: {%f, %f, %f\n", cameraTarget.x, cameraTarget.y, cameraTarget.z);
	printf("Camera Direction: {%f, %f, %f}\n", direction.x, direction.y, direction.z);
#endif
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.7, 0.7, 0.7);

	computeVectorsFromInputs();

	//ativa arrays que serão usados
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	vec3 roomCenter = vec3 (0.0f, 0.0f, 0.0f);
	Room room1 = createRoom (roomCenter, 5.0f);
	RoomNode rooms;
	rooms.room = room1;
	drawRoom (room1);

	//glutSolidTeapot (0.3);

	glFlush();
}

void init(void)
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

	//MATERIAL
	//Changing Material Properties, do Red Book (usar luz branca)
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	//atribui características ao material
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// Light
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);

	glShadeModel (GL_SMOOTH);
}

int main (int argc, char** argv) 
{
	/* Initialize the library */
	if (!glfwInit())
	{
		printf("Error while loading GLFW\n");
		return -1;
	}

	// Forcing the applicaiton to run OpenGL 4.0 or higher
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowSizeX, windowSizeY, "PICG Project 1", NULL, NULL);
	if (!window)
	{
		printf("Error while creating window\n");
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent (window);
	glfwSetCursorPos (window, windowSizeX/2, windowSizeY/2);
	glfwSetKeyCallback (window, keyboard);
	glfwSwapInterval (1);

	// Initializes the GLEW library
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW\n");
		return -1;
	}

#if MAIN_DEBUG
	// Prints the OpenGL Version on the terminal
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
#endif

	init();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		display();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
