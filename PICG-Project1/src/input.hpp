#ifndef INPUT
#define INPUT

GLint largeObjectSize;

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
        case GLFW_KEY_L:
            if (action == GLFW_PRESS)
            {
                switchLight();
            }
            break;
	}
    
#if MAIN_DEBUG
	printf("Right: {%f, %f, %f}\n", right.x, right.y, right.z);
#endif
}


void addObject (Room *room, ObjectNode *obj)
{
	if (room -> objects -> next == NULL)
	{
		room -> objects -> next = obj;
	}
	else
	{
		ObjectNode *current = room -> objects -> next;
		while (current -> next != NULL)
		{
			current = current -> next;
		}
		current -> next = obj;
	}
}

void placeObjects(Room *room)
{
    vec3 startPoint = (room -> center) - (vec3(room -> size/2, 0, room -> size/2));
    startPoint += vec3(largeObjectSize/2, 0, largeObjectSize/2);
    
    int maxRolls = floor(roomSize / largeObjectSize);
    int totalObjects = room -> obj1C + room -> obj2C;
    
    for (int i = 0; i < totalObjects; i++)
    {
        ObjectNode *newObj = (ObjectNode*) malloc(sizeof(ObjectNode));
        newObj -> next = NULL;
        newObj -> object = (Object*) malloc (sizeof(Object));
        
        if (rand() % 2 == 0)
        {
            if (room -> obj1C > 0)
            {
                newObj -> object -> model = model1;
                room -> obj1C--;
            }
            else
            {
                newObj -> object -> model = model2;
                room -> obj2C--;
            }
        }
        else
        {
            if (room -> obj2C > 0)
            {
                newObj -> object -> model = model2;
                room -> obj2C--;
            }
            else
            {
                newObj -> object -> model = model1;
                room -> obj1C--;
            }
        }
        
        int rolls = i / maxRolls;
        int columns = i % maxRolls;
        
        GLfloat offSetX = rolls * largeObjectSize;
        GLfloat offSetY = columns * largeObjectSize;
        
        vec3 position = vec3(startPoint.x + offSetX , startPoint.y, startPoint.z + offSetY);
        newObj -> object -> position = position;
        addObject(room, newObj);
    }
}

void readInput ()
{
	GLint rooms;
    
    rooms = 3;
	//scanf("%i\n", &rooms);
	createGrid(rooms, roomSize);
    
	GridNode *currentGridNode = grid;
    
	for (int i = 0; i < rooms; i++)
	{
		int obj1Ave, obj1Dev, obj2Ave, obj2Dev;
		//scanf("%i %i %i %i\n", &obj1Ave, &obj1Dev, &obj2Ave, &obj2Dev);
        Room *room = currentGridNode -> next -> room;
        obj1Ave = 50;
        obj1Dev = 0;
        obj2Ave = 50;
        obj2Dev = 0;
        
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
                printf(" Let me take an Model1 out\n");
                obj1C--;
            }
            else
            {
                printf(" Let me take an Model2 out\n");
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
