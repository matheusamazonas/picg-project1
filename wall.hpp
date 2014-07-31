#ifndef WALL
#define WALL

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

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, grassTextName);

	GLfloat texels[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1,0, 1.0, 0.0};
	
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
	//glColorPointer (3, GL_FLOAT, 0, colors);
	glVertexPointer (3, GL_FLOAT, 0, vertices);
	glTexCoordPointer (2, GL_FLOAT, 0, texels);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//glDisableClientState (GL_COLOR_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

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

