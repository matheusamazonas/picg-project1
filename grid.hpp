#ifndef GRID
#define GRID 

#ifndef ROOM
#include "room.hpp"
#endif

#define GRID_DEBUG 0
#include <math.h>

typedef struct gridNode 
{
	Room room;
	gridNode *next;
} GridNode;

void addRoom (GridNode*, Room);

GridNode (createGrid) (int elements, float roomSize)
{
	int dimension = ceil(sqrt((float)elements));

	GridNode grid;
	grid.next = NULL;

	int elementsCreated = 0;
	vec3 gridStart = vec3 (0.0f, 0.0f, 0.0f);

	GridNode current = grid;
	current.next = NULL;
	for (int i = 0; i < dimension ; i++)
	{
		for (int j = 0; j < dimension & elementsCreated < elements; j++)
		{
			vec3 center = vec3 (
					gridStart.x + 3 * i * roomSize,
					gridStart.y,
					gridStart.z + 3 * j * roomSize
					);
			Room room = createRoom (center, roomSize);
			addRoom (&grid, room);
			elementsCreated++;
		}
	}
	return grid;
}

void addRoom (GridNode *grid, Room room)
{
	GridNode *newNode = (GridNode*)malloc(sizeof(GridNode));
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
	printf("Creating room at %f %f %f\n", room.center.x, room.center.y, room.center.z);
#endif	
}

void drawGrid (GridNode *grid)
{
	GridNode *currentNode = grid -> next;
	while (currentNode != NULL)
	{
		Room room = currentNode -> room;
		drawRoom(room);
		currentNode = currentNode -> next;
	}
}
#endif
