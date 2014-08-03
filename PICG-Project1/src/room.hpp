#ifndef ROOM
#define ROOM

typedef struct
{
	vec3 center;
	GLfloat size;
	WallNode *walls;
	ObjectNode *objects;
	GLint obj1C;
	GLint obj2C;
} Room; 


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
	wallCenter = vec3 (room -> center.x, room -> center.y + offset, room -> center.z + offset);
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
