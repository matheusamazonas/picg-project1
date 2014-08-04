// ---------------- wall.hpp ----------------||
//         Author: Matheus A C de Andrade    ||
//                Loads textures             ||
// ------------------------------------------||

#ifndef WALL
#define WALL

// A wall is defined by its center, orientation and size (the room size)
// The orientation possibilites are 3: aligned with the XY plane, with the
//  YZ plane and with the XA plane
typedef struct
{
	vec3 center;
	GLint orientation;
	GLfloat size;
} Wall;

// The WallNode that describes a list of walls a room has
typedef struct wallNode
{
	Wall wall;
	struct wallNode *next;
} WallNode;

// Draw a wall using the room texture
void drawWall (Wall wall)
{
	vec3 center = wall.center;
    // The vertices offset. Later set base don wall's orientation
	GLfloat offsetX = 0, offsetY = 0, offsetZ = 0;
    // Spin factor that will change the vertices placement based
    //  on the wall orientation
	GLint spin = 1;

    // Texels are texture coordinates. Each wall's texel will
    //  map either the grass or wall textures
	GLfloat *texels = NULL;
	GLfloat grassTexels[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 0.5};
	GLfloat wallTexels[]  = {0.0, 0.5, 1.0, 0.5, 1.0, 0.0, 0.0, 0.0};

    // Based on the orientation, sets the texels, offSet and spin factor
	switch (wall.orientation)
	{	
		case 0:
			texels = grassTexels;
			offsetX = (wall.size) / 2;
			offsetZ = (wall.size) / 2;
			spin = 1;
			break;		
		case 1:
			texels = wallTexels;
			offsetY = (wall.size) / 2;
			offsetZ = (wall.size) / 2;
			spin = 1;
			break;		
		case 2:
			texels = wallTexels;
			offsetX = (wall.size) / 2;
			offsetY = (wall.size) / 2;
			spin = -1;
			break;
	}

    // Sets the walls vertices using the data set by the orientation
	GLfloat vertices[12] = {
		center.x - offsetX, center.y - offsetY, 		center.z - offsetZ,
		center.x + offsetX, center.y + offsetY * spin,  center.z - offsetZ,
		center.x + offsetX, center.y + offsetY, 		center.z + offsetZ,
		center.x - offsetX, center.y - offsetY * spin,	center.z + offsetZ
	};

    // Sequence of gl calls to draw a wall
	glEnable(GL_TEXTURE_2D);
    
    glActiveTexture(GL_TEXTURE0);
    
    glBindTexture(GL_TEXTURE_2D, texNames[0]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, texels);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableClientState (GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);

#if WALL_DEBUG
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

