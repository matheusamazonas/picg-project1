#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.hpp"
using namespace glm;

vec3 cameraPos = vec3 (0.0f, 0.0f, -2.0f);
vec3 cameraFront = vec3 (0.0f, 0.0f, 1.0f);
vec3 cameraUp = vec3 (0.0f, 1.0f, 0.0f);

float camSpeed = 0.05f;
float mouseSpeed = 0.005f;
GLFWwindow* window;
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
float deltaTime;
double windowSizeX = 800, windowSizeY = 600;

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	vec3 right = cross (cameraFront, cameraUp);
	switch (key) 
	{
		case GLFW_KEY_W:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos += cameraFront * deltaTime * camSpeed;
			}
			break;
		case GLFW_KEY_S:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos -= cameraFront * deltaTime * camSpeed;
			}
			break;
		case GLFW_KEY_A:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos -= right * deltaTime * camSpeed;
			}
			break;
		case GLFW_KEY_D:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos += right * deltaTime * camSpeed;
			}
			break;
	}
	//printf("Camera position: {%f, %f, %f}\n", cameraPos.x, cameraPos.y, cameraPos.z);
	printf("Camera front: {%f, %f, %f\n", cameraFront.x, cameraFront.y, cameraFront.z);
}

void mouse (GLFWwindow* window, double xPos, double yPos)
{
	vec3 right = vec3(
			sin(horizontalAngle - 3.14f/2.0f), 
			0,
			cos(horizontalAngle - 3.14f/2.0f)
			);	
}

void computeMatricesFromInputs(void)
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
	cameraFront = vec3(
			cos(verticalAngle) * sin(horizontalAngle), 
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
			);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Compute the MVP matrix from keyboard and mouse input
	computeMatricesFromInputs();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	gluLookAt(                        // Set camera position and orientation
			cameraPos.x, cameraPos.y, cameraPos.z,              			
			cameraFront.x, cameraFront.y, cameraFront.z,                // View point (x,y,z)
			cameraUp.x, cameraUp.y, cameraUp.z                 // Up-vector (x,y,z)
			);

	//Mais sobre os comandos de push e pop matrices aqui: 
	//http://www.opengl.org/sdk/docs/man2/xhtml/glPushMatrix.xml
	//	glPushMatrix();

	glColor3f(0.7, 0.7, 0.7);

	//Mais sobre os comandos de push e pop matrices aqui: 
	//http://www.opengl.org/sdk/docs/man2/xhtml/glPushMatrix.xml
	//glPushMatrix();

	static GLfloat vertices[] = {
		-0.5, -0.5, 0.0, 
		0.5, -0.5, 0.0, 
		0.5, 0.5, 0.0, 
		-0.5, 0.5, 0.0
	};
	static GLfloat colors[] = {
		1.0, 1.0, 1.0, 
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 
		1.0, 1.0, 1.0

	};

	//ativa arrays que serão usados
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	//associa dados aos arrays
	glColorPointer (3, GL_FLOAT, 0, colors);
	glVertexPointer (3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//retira cabeça da pilha de atributos
	//glPopAttrib();

	//retira a matriz de transformação da cabeça da pilha
	//glPopMatrix();

	glFlush();
}

void init(void)
{
	// Light
	/*
	   GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	   GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	   GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
	   glLightfv (GL_LIGHT0, GL_POSITION, light_position);
	   glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	   glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	   glEnable(GL_LIGHTING);
	   glEnable(GL_LIGHT0);

	   glEnable(GL_DEPTH_TEST);
	 */
}

int main (int argc, char** argv) 
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// Forcing the applicaiton to run OpenGL 4.0 or higher
	// The RedBook is based on OpenGL 4.3
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowSizeX, windowSizeY, "Example 1-1", NULL, NULL);
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
	glfwSetCursorPosCallback (window, mouse); 
	glfwSwapInterval (1);

	// Initializes the GLEW library
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW\n");
		return -1;
	}


	// Prints the OpenGL Version on the terminal
	//printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

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
