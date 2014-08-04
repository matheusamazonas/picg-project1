// ---------------- room.hpp ----------------||
//         Author: Matheus A C de Andrade    ||
// Rooms that compose the grid and have      ||
// elements                                  ||
// ------------------------------------------||

#ifndef ROOM
#define ROOM

// The room struct. Each room has a center, a size (n * n),
//  walls and objects inside it.
typedef struct
{
	vec3 center;
	GLfloat size;
	WallNode *walls;
	ObjectNode *objects;
	GLint obj1C;
	GLint obj2C;
} Room; 

// Add an object to the given room's object list (to the end)
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

// This is called during the progrma input session. It places objects
//  randomly based on its size and how many objects it should have of
//  each type (1 or 2). the placement is a grid placement, placing
//  columns first
void placeObjects(Room *room)
{
    vec3 startPoint = (room -> center) - (vec3(room -> size/2, 0, room -> size/2));
    startPoint += vec3(largeObjectSize/2, 0, largeObjectSize/2);
    
    // Maximum numbers of rolls (and columns also) that the room can support
    int maxRolls = floor(roomSize / largeObjectSize);
    int totalObjects = room -> obj1C + room -> obj2C;
    
    // While the numbers of objects created/placed is less than how many
    //  we can to create, place new objects
    for (int i = 0; i < totalObjects; i++)
    {
        ObjectNode *newObj = (ObjectNode*) malloc(sizeof(ObjectNode));
        newObj -> next = NULL;
        newObj -> object = (Object*) malloc (sizeof(Object));
        
        // Places either a obj1 or obj2. Made this just to place
        //  them randomly. It's visually good.
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

// Creates a room centered in a given point and with dimension (size * size)
// This creation is dynamic. It creates a room with 3 walls placed based on
//  its center and size. Nothing else.
Room* createRoom (vec3 center, float size)
{
	GLfloat offset = size / 2;

	Room *room = (Room*) malloc(sizeof(Room));
	room -> center = center;
	room -> size = size;
	room -> objects = NULL;

	Wall floor;
	floor.center = room -> center;
	floor.size = size;
	floor.orientation = 0;

	Wall wall1;
	vec3 wallCenter = vec3 (room -> center.x - offset, room -> center.y + offset, room -> center.z);
	wall1.center = wallCenter;
	wall1.size = room -> size;
	wall1.orientation = 1;

	Wall wall2;
	wallCenter = vec3 (room -> center.x + offset, room -> center.y + offset, room -> center.z);
	wall2.center = wallCenter;
	wall2.size = room -> size;
	wall2.orientation = 1;

	Wall wall3;
	wallCenter = vec3 (room -> center.x, room -> center.y + offset, room -> center.z - offset);
	wall3.center = wallCenter;
	wall3.size = room -> size;
	wall3.orientation = 2;

	WallNode *walls;
	walls = (WallNode*) malloc(sizeof(WallNode));
	walls -> wall = floor;

	WallNode *wallNode1;
	wallNode1 = (WallNode*) malloc(sizeof(WallNode));
	wallNode1 -> wall = wall1;
	walls -> next = wallNode1;

	WallNode *wallNode2;
	wallNode2 = (WallNode*) malloc(sizeof(WallNode));
	wallNode2 -> wall = wall2;
	wallNode1 -> next = wallNode2;

	WallNode *wallNode3;
	wallNode3 = (WallNode*) malloc(sizeof(WallNode));
	wallNode3 -> wall = wall3;
	wallNode2 -> next = wallNode3;

	wallNode3 -> next = NULL;

	room -> walls = walls;

	return room; 	
}

// Draws a room by simply calling each wall and object draw method
void drawRoom (Room *room)
{
	WallNode *current = room -> walls;
	while (current != NULL)
	{	
		Wall wall = current -> wall;
		drawWall(wall);
		current = current -> next;
	}

	ObjectNode *currentObj = room -> objects -> next;
	while (currentObj != NULL)
	{
		drawModel(currentObj -> object -> model, currentObj -> object -> position);	
		currentObj = currentObj -> next; 
	}	
#if ROOM_DEBUG
	printf("Drawing room at %f, %f, %f\n", room -> center.x, room -> center.y, room -> center.z);
#endif

}
#endif
