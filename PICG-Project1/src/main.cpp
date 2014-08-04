// ---------------- main.hpp ----------------||
//         Author: Matheus A C de Andrade    ||
//           Just good old main.cpp          ||
// ------------------------------------------||

#include "common.hpp"

// Makes MVP matrices changes based on input
void computeVectorsFromInputs ()
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	deltaTime = (float)(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Compute new orientation
	horizontalAngle = mouseSpeed * (float)(windowSizeX/2 - xpos);
	verticalAngle   = mouseSpeed * (float)(windowSizeY/2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	cameraTarget = vec3 (
			cos (verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
			);
    vec3 cameraDirection = cameraPos + cameraTarget;
    
    // Changes the projection matrix base don camera data
	glMatrixMode(GL_PROJECTION);
    mat4 projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 400.0f);
    mat4 view = lookAt(cameraPos, cameraDirection, cameraUp);
    glLoadIdentity();
    glLoadMatrixf(value_ptr(projection * view));

#if MAIN_DEBUG
	printf("\nCursor position (%f, %f)\n", xpos, ypos);
	printf("H_Angle: %f V_Angle %f\n", horizontalAngle, verticalAngle);
	printf("Camera position: {%f, %f, %f}\n", cameraPos.x, cameraPos.y, cameraPos.z);
	printf("Camera target: {%f, %f, %f\n", cameraTarget.x, cameraTarget.y, cameraTarget.z);
#endif
}

// The display function that is called at each frame
void display (void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.7, 0.7, 0.7);

    // Makes MVP matrices changes based on input
	computeVectorsFromInputs();
    
    // The drawing.
	drawGrid(grid);
    
	glFlush();
}

// Initialization. Models, textures, program input and graphics definitions
void init (void)
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

    // Model loading based on each scale
	model1 = readModel (model1Path, model1Scale);
	model1 -> size = model1Size;
	model2 = readModel (model2Path, model2Scale);
	model2 -> size = model2Size;
    
    // Textures configuration in general
	configTextMode();

    // Read the program input (not user input) to determinw hoe many rooms
    //  and theirs objects will be drawn
	readInput();

	// Light. The light switch is made in the input.cpp.
    // Switch it pressing the key L. Do it!
    if (light)
    {
        GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
        GLfloat light_diffuse[] = {0.9, 0.9, 0.9, 0.0};
        GLfloat light_ambient[] = {1.4, 1.4, 1.4, 0.0};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }

	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
}


// MAIN!!
int main (int argc, char** argv) 
{
	/* Initialize the library */
	if (!glfwInit())
	{
		printf("Error while loading GLFW\n");
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowSizeX, windowSizeY, "PICG Project 1", NULL, NULL);
	if (!window)
	{
		printf("Error while creating window\n");
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetCursorPos(window, windowSizeX/2, windowSizeY/2);
	glfwSetKeyCallback(window, keyboard);
	glfwSwapInterval(1);

#if MAIN_DEBUG
	// Prints the OpenGL Version on the terminal
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
#endif

    // Initialization. Models, textures, program input
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
