#ifndef WALL
#define WALL

#define WALL_DEBUG 0

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


void drawWall (Wall wall)
{
	vec3 center = wall.center;
	float offsetX = 0, offsetY = 0, offsetZ = 0;
	int spin;
	vec3 color; 

	switch (wall.orientation)
	{	
		case 0:
			offsetX = (wall.size) / 2;
			offsetZ = (wall.size) / 2;
			spin = 1;
			color = vec3 (0.8f, 0.2f, 0.2f);
			break;		
		case 1:
			offsetY = (wall.size) / 2;
			offsetZ = (wall.size) / 2;
			spin = 1;
			color = vec3 (0.2f, 0.2f, 0.8f);
			break;		
		case 2:
			offsetX = (wall.size) / 2;
			offsetY = (wall.size) / 2;
			spin = -1;
			color = vec3 (0.2f, 0.8f, 0.2f);
			break;
	}

	GLfloat vertices[12] = {
		center.x - offsetX, center.y - offsetY, 		center.z - offsetZ,
		center.x + offsetX, center.y + offsetY * spin,  center.z - offsetZ,
		center.x + offsetX, center.y + offsetY, 		center.z + offsetZ,
		center.x - offsetX, center.y - offsetY * spin,	center.z + offsetZ
	};

	GLfloat colors[] = {
		color.x, color.y, color.z, 
		color.x, color.y, color.z,	
		color.x, color.y, color.z, 
		color.x, color.y, color.z 	
	};

	//associa dados aos arrays
	glColorPointer (3, GL_FLOAT, 0, colors);
	glVertexPointer (3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//glDisableClientState(GL_COLOR_ARRAY);

#if WALL_DEBUG
	printf("Wall color: %f %f %f\n", color.x, color.y, color.z);
	printf("OffsetX: %f OffsetY: %f OffsetZ: %f\n", offsetX, offsetY, offsetZ);
	printf("Wall center: %f %f %f Wall Size: %f Wall Orientation: %d\n", center.x, center.y, center.z, wall.size, wall.orientation);
	printf("Vertices:\n%f %f %f\n%f %f %f\n%f %f %f\n%f %f %f\n",
			vertices[0], vertices[1],  vertices[2],
			vertices[3], vertices[4],  vertices[5],
			vertices[6], vertices[7],  vertices[8],
			vertices[9], vertices[10], vertices[11]);
#endif
}

#endif

