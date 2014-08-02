#ifndef INPUT
#define INPUT

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

void readInput ()
{
	GLint rooms;

    rooms = 1;
	//scanf("%i\n", &rooms);
	createGrid(rooms, 20);

	GridNode *currentRoom = grid;

	for (int i = 0; i < rooms; i++)
	{
		int obj1Ave, obj1Dev, obj2Ave, obj2Dev;
		//scanf("%i %i %i %i\n", &obj1Ave, &obj1Dev, &obj2Ave, &obj2Dev);
			Room *room = currentRoom -> next -> room;
        obj1Ave = 3;
        obj1Dev = 2;
        obj2Ave = 6;
        obj2Dev = 3;

		srand((unsigned int) time(NULL));
		int max1 = obj1Ave + obj1Dev;
		int min1 = obj1Ave - obj1Dev;
		int obj1C = rand() % (max1-min1 + 1) + min1;

		int max2 = obj2Ave + obj2Dev;
		int min2 = obj2Ave - obj2Dev;
		int obj2C = rand() % (max2-min2 + 1) + min2;

		room -> obj1C = obj1C;
		room -> obj2C = obj1C;
		room -> objects = (ObjectNode*) malloc (sizeof(ObjectNode));
		room -> objects -> next = NULL;

		if (obj1C > 0)
		{

			for (int i = 0; i < room -> obj1C; i++)
			{
				ObjectNode *newObj = (ObjectNode*) malloc (sizeof(ObjectNode));
				newObj -> next = NULL;
				newObj -> object = (Object*) malloc (sizeof(Object));
				newObj -> object -> model = model1;
				vec3 position = vec3(room -> center.x + i, room -> center.y, room -> center.z + i);
				newObj -> object -> position = position;

				addObject(room, newObj);
			}
		}

		if (obj2C > 0)
		{
			for (int i = 0; i < room -> obj2C; i++)
			{
				ObjectNode *newObj = (ObjectNode*) malloc (sizeof(ObjectNode));
				newObj -> next = NULL;
				newObj -> object = (Object*) malloc (sizeof(Object));
				newObj -> object -> model = model1;
				vec3 position = vec3(room -> center.x - i*2, room -> center.y + 1, room -> center.z - i);
				newObj -> object -> position = position;

				addObject(room, newObj);
			}

		}
		currentRoom = currentRoom -> next;
#if INPUT_DEBUG
		printf("Read %i %i %i %i\n", obj1Ave, obj1Dev, obj2Ave, obj2Dev);
		printf("obj1Ave: %i obj1Dev: %i\n", obj1Ave, obj1Dev);
		printf("max1: %i min1: %i obj1: %i\n", max1, min1, obj1C);
#endif
	}	
}
#endif
