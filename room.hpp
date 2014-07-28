#ifndef ROOM
#define ROOM

#define ROOM_DEBUG 1

typedef struct
{
	vec3 center;
	int orientation;
	float size;
} Wall;

typedef struct wallNode
{
	Wall wall;
	struct wallNode *next;
} WallNode;

typedef struct
{
	vec3 center;
	float size;	
	WallNode *walls;
} Room; 

typedef struct roomNode 
{
	Room room;
	struct roomNode *next;
} RoomNode;


Room createRoom (vec3 center, float size)
{
	int wallCount = 4;
	float offset = size / 2;

	Room room;
	room.center = center;
	room.size = size;
	
	Wall floor;
	floor.center = room.center;
	floor.size = size;
	floor.orientation = 0;
	
	Wall wall1;
	vec3 wallCenter = vec3 (room.center.x - offset, room.center.y + offset, room.center.z);
	wall1.center = wallCenter;
	wall1.size = room.size;
	wall1.orientation = 1;

	Wall wall2;
	wallCenter = vec3 (room.center.x + offset, room.center.y + offset, room.center.z);
	wall2.center = wallCenter;
	wall2.size = room.size;
	wall2.orientation = 1;

	Wall wall3;
	wallCenter = vec3 (room.center.x, room.center.y + offset, room.center.z + offset);
	wall3.center = wallCenter;
	wall3.size = room.size;
	wall3.orientation = 2;

	WallNode *walls;
	walls = (WallNode*)malloc(sizeof(WallNode));
	walls -> wall = floor;

	WallNode *wallNode1;
	wallNode1 = (WallNode*)malloc(sizeof(WallNode));
	wallNode1 -> wall = wall1;
	walls -> next = wallNode1;

	WallNode *wallNode2;
	wallNode2 = (WallNode*)malloc(sizeof(WallNode));
	wallNode2 -> wall = wall2;
	wallNode1 -> next = wallNode2;

	WallNode *wallNode3;
	wallNode3 = (WallNode*)malloc(sizeof(WallNode));
	wallNode3 -> wall = wall3;
	wallNode2 -> next = wallNode3;

	wallNode3 -> next = NULL;
	
	room.walls = walls;

	return room; 	
}


void drawWall (Wall *wall)
{
	vec3 center = wall -> center;
	float offsetX = 0, offsetY = 0, offsetZ = 0;
	GLfloat vertices[12];

	switch (wall -> orientation)
	{	
		case 0:
			offsetX = (wall -> size) / 2;
			offsetZ = (wall -> size) / 2;
			break;		
		case 1:
			offsetY = (wall -> size) / 2;
			offsetZ = (wall -> size) / 2;
			break;		
		case 2:
			offsetX = (wall -> size) / 2;
			offsetY = (wall -> size) / 2;
			break;
	}

	if (wall -> orientation == 0 || wall -> orientation == 1)	
	{
		vertices[0] = center.x - offsetX;
		vertices[1] = center.y - offsetY;
		vertices[2] = center.z - offsetZ;
		vertices[3] = center.x + offsetX;
		vertices[4] = center.y + offsetY;
		vertices[5] = center.z - offsetZ;
		vertices[6] = center.x + offsetX;
		vertices[7] = center.y + offsetY;
		vertices[8] = center.z + offsetZ;
		vertices[9] = center.x - offsetX;
		vertices[10] = center.y - offsetY;
		vertices[11] = center.z + offsetZ;
	}
	else
	{ 
		vertices[0] = center.x - offsetX;
		vertices[1] = center.y - offsetY;
		vertices[2] = center.z - offsetZ;
		vertices[3] = center.x + offsetX;
		vertices[4] = center.y - offsetY;
		vertices[5] = center.z - offsetZ;
		vertices[6] = center.x + offsetX;
		vertices[7] = center.y + offsetY;
		vertices[8] = center.z + offsetZ;
		vertices[9] = center.x - offsetX;
		vertices[10] = center.y + offsetY;
		vertices[11] = center.z + offsetZ;
	}

	static GLfloat colors[] = {
		1.0, 1.0, 1.0, 
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 
		1.0, 1.0, 1.0
	};

	//associa dados aos arrays
	glColorPointer (3, GL_FLOAT, 0, colors);
	glVertexPointer (3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

#if ROOM_DEBUG
	printf("OffsetX: %f OffsetY: %f OffsetZ: %f\n", offsetX, offsetY, offsetZ);
	printf("Wall center: %f %f %f Wall Size: %f Wall Orientation: %d\n", center.x, center.y, center.z, wall -> size, wall -> orientation);
	printf("Vertices:\n%f %f %f\n%f %f %f\n%f %f %f\n%f %f %f\n",
			vertices[0], vertices[1],  vertices[2],
			vertices[3], vertices[4],  vertices[5],
			vertices[6], vertices[7],  vertices[8],
			vertices[9], vertices[10], vertices[11]);
#endif
}

void drawRoom (Room room)
{
	WallNode *current = room.walls;
	while (current != NULL)
	{
		Wall *wall = &current -> wall;
		drawWall (wall);
		current = current -> next;
	}
#if ROOM_DEBUG
	printf("Drawing room at %f, %f, %f\n", room.center.x, room.center.y, room.center.z);
#endif

}
#endif
