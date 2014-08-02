#ifndef GRID
#define GRID 

typedef struct gridNode 
{
	Room *room;
	gridNode *next;
} GridNode;

void addRoom (GridNode*, Room*);

GridNode *grid;
vec3 center;
GLfloat planeSize = 100.0f;

GridNode* createGrid (int rooms, float roomSize)
{
	GLint dimension = ceil(sqrt (rooms));
	center = vec3(dimension/2, -0.1f, dimension/2);
	GLint elementsCreated = 0;
	vec3 gridStart = vec3(0.0f, 0.0f, 0.0f);

	grid = (GridNode*) malloc (sizeof(GridNode));
	grid -> next = NULL;

	GridNode *current = grid;
	current -> next = NULL;
	
	for (int i = 0; i < dimension ; i++)
	{
		for (int j = 0; j < dimension & elementsCreated < rooms; j++)
		{
			vec3 center = vec3 (
					gridStart.x + 3 * i * roomSize,
					gridStart.y,
					gridStart.z + 3 * j * roomSize
					);
			Room *room = createRoom(center, roomSize);
			if (room == NULL)
			{
				printf("Error while creating room\n");
			}
			addRoom(grid, room);
			elementsCreated++;
		}
	}
	return grid;
}

void addRoom (GridNode *grid, Room *room)
{
	GridNode *newNode = (GridNode*) malloc (sizeof(GridNode));
	newNode -> room = room;
	newNode -> next = NULL;

	if (grid -> next == NULL)
	{
		grid -> next = newNode;
	}
	else
	{
		GridNode *current = grid;
		while (current -> next != NULL)
		{
			current = current -> next;
		} 
		current -> next = newNode;
	}
#if GRID_DEBUG
	printf("Creating room at %f %f %f\n", room -> center.x, room -> center.y, room -> center.z);
#endif	
}

void drawPlane ()
{
	GLfloat vertices[12] = {
		center.x - planeSize, center.y, center.z - planeSize,
		center.x + planeSize, center.y, center.z - planeSize,
		center.x + planeSize, center.y, center.z + planeSize,
		center.x - planeSize, center.y, center.z + planeSize 
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawGrid (GridNode *grid)
{
	drawPlane();
	GridNode *currentNode = grid -> next;
	while (currentNode != NULL)
	{
		Room *room = currentNode -> room;
		drawRoom (room);
		currentNode = currentNode -> next;
	}
}
#endif
