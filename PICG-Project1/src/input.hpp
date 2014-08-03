#ifndef INPUT
#define INPUT

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


void readInput ()
{
	GLint rooms;
	scanf("%i\n", &rooms);
    
    if (rooms > maxRooms)
    {
        printf("Too many rooms! I can draw only 10\n");
        rooms = maxRooms;
    }
	
    createGrid(rooms, roomSize);
	GridNode *currentGridNode = grid;
    
	for (int i = 0; i < rooms; i++)
	{
		int obj1Ave, obj1Dev, obj2Ave, obj2Dev;
		scanf("%*s %*s %i %i %*s %i %i", &obj1Ave, &obj1Dev, &obj2Ave, &obj2Dev);
        Room *room = currentGridNode -> next -> room;
        
		srand((unsigned int) time(NULL));
		int max1 = obj1Ave + obj1Dev;
		int min1 = obj1Ave - obj1Dev;
		int obj1C = rand() % (max1-min1 + 1) + min1;
        
		int max2 = obj2Ave + obj2Dev;
		int min2 = obj2Ave - obj2Dev;
		int obj2C = rand() % (max2-min2 + 1) + min2;
        
        if (model1Size > model2Size)
        {
            largeObjectSize = model1Size;
        }
        else
        {
            largeObjectSize = model2Size;
        }
        
        int maxObjects = pow((roomSize / largeObjectSize), 2);
        while (obj1C + obj2C > maxObjects)
        {
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
