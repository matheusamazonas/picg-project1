#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


float camPositionX = 0, camPositionY = 0, camPositionZ = 0;
float camFrontX = 0, camFrontY = 0, camFrontZ = 1;
float camUpX = 0, camUpY = 1, camUpZ = 0;
float camSpeed = 0.05f;

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

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key) 
	{
		case GLFW_KEY_W:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				camPositionZ += camSpeed * camFrontZ;
				printf("Pressed up\n");
			}
			break;
		case GLFW_KEY_S:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				camPositionZ -= camSpeed * camFrontZ;
				printf("Pressed down\n");
			}
			break;
		case GLFW_KEY_A:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				camPositionX += camSpeed;
				printf("Pressed left\n");
			}
			break;
		case GLFW_KEY_D:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				camPositionX -= camSpeed;
				printf("Pressed right\n");
			}
			break;
	}
	printf("Camera position: {%f, %f, %f}\n", camPositionX, camPositionY, camPositionZ);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);


	gluLookAt(                        // Set camera position and orientation
			camPositionX, camPositionY, camPositionZ,              			
			camFrontX, camFrontY, camFrontZ,                // View point (x,y,z)
			camUpX, camUpY, camUpZ                 // Up-vector (x,y,z)
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


int main (int argc, char** argv) 
{
	GLFWwindow* window;

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
	window = glfwCreateWindow(512, 512, "Example 1-1", NULL, NULL);
	if (!window)
	{
		printf("Error while creating window\n");
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback (window, keyboard);
	glfwSwapInterval(1);

	// Initializes the GLEW library
	glewExperimental = GL_TRUE;
	glewInit();

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
