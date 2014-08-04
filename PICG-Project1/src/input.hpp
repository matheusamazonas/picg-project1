// ---------------- input.hpp ---------------||
//         Author: Matheus A C de Andrade    ||
//             Treats user input             ||
// ------------------------------------------||

#ifndef INPUT
#define INPUT


// Turns light on and off based on its actual state
void switchLight ()
{
    light = !light;
    if (light)
    {
        glEnable(GL_LIGHTING);
    }
    else
    {
        glDisable(GL_LIGHTING);
    }
}

// Deals with all keyboard input using GLFW3:
//  WSAD keys to navigate (forward, backward, left, right)
//  L to switch light
//  Left Shift to boost movement speed
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
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
				cameraPos += cameraTarget * deltaTime * camSpeed * speedBoost;
			}
			break;
		case GLFW_KEY_S:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos -= cameraTarget * deltaTime * camSpeed * speedBoost;
			}
			break;
		case GLFW_KEY_D:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos += right * deltaTime * camSpeed * speedBoost;
			}
			break;
		case GLFW_KEY_A:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				cameraPos -= right * deltaTime * camSpeed * speedBoost;
			}
			break;
        case GLFW_KEY_L:
            if (action == GLFW_PRESS)
            {
                switchLight();
            }
            break;
        case GLFW_KEY_LEFT_SHIFT:
            if (action == GLFW_PRESS)
            {
                speedBoost = 2.5f;
            }
            else if (action == GLFW_RELEASE)
            {
                speedBoost = 1.0f;
            }
            break;
	}
#if MAIN_DEBUG
	printf("Right: {%f, %f, %f}\n", right.x, right.y, right.z);
#endif
}

// Read the initial input (may be writing in the console, or ridirecting
//  a text file. Also deals with the logic behind room elements. The input
//  follows the model:
//  3
//  s1 o1 3 2 o2 6 3
//  s2 o1 3 0 o2 6 1
//  s3 o1 8 1 o2 2 2
// Where the first line indicates how many rooms the grid will have (but
//  there's a maximum). The follow lines indicate the avarage and deviation
//  for each object (there are only 2 object types in each room)
void readInput ()
{
	GLint rooms;
    // Reads the input to check how many rooms will be drawn
	scanf("%i\n", &rooms);
    
    // Caps the number of rooms if greater than the maximum
    //  A big size may decrease application performance
    if (rooms > maxRooms)
    {
        printf("Too many rooms! I can draw only 10\n");
        rooms = maxRooms;
    }
	
    // Creates the grid with empty rooms
    GridNode *currentGridNode = createGrid(rooms, roomSize);
    
    // Reads the input of each room and populates it base don the input
	for (int i = 0; i < rooms; i++)
	{
		int obj1Ave, obj1Dev, obj2Ave, obj2Dev;
		scanf("%*s %*s %i %i %*s %i %i", &obj1Ave, &obj1Dev, &obj2Ave, &obj2Dev);
        Room *room = currentGridNode -> next -> room;
        
        // Gets a random number between the average and the deviation
        // Simple random number here. No normal distribution
		srand((unsigned int) time(NULL));
		int max1 = obj1Ave + obj1Dev;
		int min1 = obj1Ave - obj1Dev;
		int obj1C = rand() % (max1-min1 + 1) + min1;
        
		int max2 = obj2Ave + obj2Dev;
		int min2 = obj2Ave - obj2Dev;
		int obj2C = rand() % (max2-min2 + 1) + min2;
        
        // Checks which model is the largest one. To simplify the program
        //  we assume that both models are as large as the largest one
        if (model1Size > model2Size)
        {
            largeObjectSize = model1Size;
        }
        else
        {
            largeObjectSize = model2Size;
        }
        
        // Calculates how many objects we can put ion the room based on the
        //  room's size and the largest model's size
        int maxObjects = pow((roomSize / largeObjectSize), 2);
        
        // If the number of objects we want to create is bigger than the maximum,
        //  take one object randomly (between obj1 and obj2)
        while (obj1C + obj2C > maxObjects)
        {
            // Checks if the numbers of objects is bigger than the maximum
            printf("I can't put %i in this room,I can put only %i", obj1C + obj2C, maxObjects);
            if (rand() % 2 == 0)
            {
                printf(" Let me take a Model1 out\n");
                obj1C--;
            }
            else
            {
                printf(" Let me take a Model2 out\n");
                obj2C--;
            }
        }
        
        room -> obj1C = obj1C;
        room -> obj2C = obj2C;
        room -> objects = (ObjectNode*) malloc(sizeof(ObjectNode));
        room -> objects -> next = NULL;
        // Calls the room's placement function
        placeObjects(room);
		currentGridNode = currentGridNode -> next;
        
#if INPUT_DEBUG
		printf("Read %i %i %i %i\n", obj1Ave, obj1Dev, obj2Ave, obj2Dev);
		printf("obj1Ave: %i obj1Dev: %i\n", obj1Ave, obj1Dev);
		printf("max1: %i min1: %i obj1: %i\n", max1, min1, obj1C);
#endif
	}
}
#endif
