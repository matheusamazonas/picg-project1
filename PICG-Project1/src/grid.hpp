// ---------------- grid.hpp ----------------||
//         Author: Matheus A C de Andrade    ||
//             Just defines objects          ||
// ------------------------------------------||

#ifndef GRID
#define GRID 

// A GridNode as an element of the Grid. It just contains a room
//  and the next element.
typedef struct gridNode 
{
	Room *room;
	gridNode *next;
} GridNode;

void addRoom (GridNode*, Room*);

// The grid itself (empty list head) and its center
GridNode *grid;
vec3 gridCenter;

// Method that creates a grid based on the number of rooms and the
//  room size (same for all the rooms). The grid will be always
//  created starting on its center
GridNode* createGrid (int rooms, float roomSize)
{
    // The grid dimension (dimension x dimension) so the grid is
    //  as "squared" as possible
	GLint gridDimension = ceil(sqrt (rooms));
	gridCenter = vec3(gridDimension/2, -0.1f, gridDimension/2);
	GLint elementsCreated = 0;

	grid = (GridNode*) malloc(sizeof(GridNode));
	grid -> next = NULL;

	GridNode *current = grid;
	current -> next = NULL;
	
    // Starts to create the grid for real. Creates as many rooms were
    //  requested, always keeping them 1-roomSize apart from each other
	for (int i = 0; i < gridDimension ; i++)
	{
		for (int j = 0; j < gridDimension & elementsCreated < rooms; j++)
		{
			vec3 roomCenter = vec3 (
					gridCenter.x + 2 * i * roomSize,
					gridCenter.y,
					gridCenter.z + 2 * j * roomSize
					);
			Room *room = createRoom(roomCenter, roomSize);
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

// Adds a room to the given Grid. Just to remember that the
//  first gridNode is the empty head
void addRoom (GridNode *grid, Room *room)
{
	GridNode *newNode = (GridNode*) malloc(sizeof(GridNode));
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

// Draws an empty plane underneath the rooms using vertex array
void drawPlane ()
{
	GLfloat vertices[12] = {
		gridCenter.x - planeSize, gridCenter.y - 1, gridCenter.z - planeSize,
		gridCenter.x + planeSize, gridCenter.y - 1, gridCenter.z - planeSize,
		gridCenter.x + planeSize, gridCenter.y - 1, gridCenter.z + planeSize,
		gridCenter.x - planeSize, gridCenter.y - 1, gridCenter.z + planeSize
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

// Draws a grid simply by drawing the plane and running on the rooms list
//  and drawing each room. Simple like that.
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
