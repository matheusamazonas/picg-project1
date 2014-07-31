#ifndef MODEL
#define MODEL

#include <string>
#include <stdio.h>
using namespace std;

typedef struct 
{
	GLfloat *vertices; 
	//GLuint *faces;
	GLfloat *normals;
	GLfloat *texCoord; 
	long vertexCount;
	//long facesCount;
	long normalsCount;
	long textCoorCount;
	float scale;
	float range;
} Model;

Model model;
FILE *fptr;
GLfloat *rawVertex;
GLfloat *rawNormals;
GLfloat *rawTexCoord;

GLfloat *finalVertex;
GLfloat *finalNormals;
GLfloat *finalTexCoord;

void addVertice (long *size, float x, float y, float z, long position)
{
	position = position * 3;
//	printf("Entered to insert %f %f %f at %li with size %li\n", x, y, z, position, *size);
	if (position  >= *size - 3)
	{
		*size += 100;
		//printf("Realocating to %li\n", *size);
		rawVertex = (GLfloat*) realloc (rawVertex, sizeof(GLfloat) * (*size));
		if (rawVertex == NULL)
		{
			printf("Error trying to reallocate memory\n");
		}
	}

	rawVertex[position]   = (GLfloat) x * model.scale;
	rawVertex[position+1] = (GLfloat) y * model.scale;
	rawVertex[position+2] = (GLfloat) z * model.scale;
#if MODEL_DEBUG
	//printf("Ver: %f %f %f at pos %li Size:%li\n", 
	//		rawVertex[position], rawVertex[position+1], rawVertex[position+2], position, *size);
#endif
}

void addNormal (long *size, float x, float y, float z, long position)
{
	position = position * 3;
	if (position >= *size - 3)
	{
		*size += 100;
		rawNormals = (GLfloat*) realloc (rawNormals, sizeof(GLfloat) * (*size));
		if (rawNormals == NULL)
		{
			printf("Error trying to reallocate memory\n");
		}
	}

	rawNormals[position]   = (GLfloat) x;
	rawNormals[position+1] = (GLfloat) y;
	rawNormals[position+2] = (GLfloat) z;
#if MODEL_DEBUG
	//printf("Nor: % .3f % .3f % .3f at pos %li NSize:%li\n", x, y, z, position, *size);
#endif
}


void addTexCoord (long *size, float u, float t, long position)
{
	position = position * 3;
	if (position >= *size - 3)
	{
		*size += 100;
		rawTexCoord = (GLfloat*) realloc (rawTexCoord, sizeof(GLfloat) * (*size));
		if (rawTexCoord == NULL)
		{
			printf("Error trying to reallocate memory\n");
		}
	}
	
	rawTexCoord[position] 	 = (GLfloat) u;
	rawTexCoord[position+1] = (GLfloat) t;
#if MODEL_DEBUG
	//printf("TexCoord: % .3f % .3f at pos %li TCSize:%li\n", u, t, position, *size);
#endif
}

void addFace (int v1, int v2, int v3, int n1, int n2, int n3, int t1, int t2, int t3, int position, long *size)
{
	//GLfloat *vertex = model.vertices;
	//GLfloat *normals = model.normals;
	//GLfloat *tex = model.texCoord;

	printf("Setting face %i size: %li v1: %i v2: %i v3: %i\n", position, *size, v1, v2, v3);
	position = position * 3;
	if (position >= *size - 3)
	{	
		*size += 1000;
		printf("Realocating final Vertex to %li\n", *size);
		GLfloat *temp = (GLfloat*) realloc (finalVertex, sizeof(GLfloat) * (*size));
		//finalVertex = (GLfloat*) realloc (finalVertex, sizeof(GLfloat) * (*size));
		if (temp == NULL)
		{
			printf("Error trying to reallocate memory\n");
		}
		else
		{
			finalVertex = temp;
		}
	}

	v1--;
	v2--;
	v3--;

	v1 *= 3;
	v2 *= 3;
	v3 *= 3;
	printf("Here\n");
	printf("Adding vertice %i: %f %f %f\n",   v1, rawVertex[v1], rawVertex[v1+1], rawVertex[v1+2]);
	printf("Adding vertice %i: %f %f %f\n",   v2, rawVertex[v2], rawVertex[v2+1], rawVertex[v2+2]);
	printf("Adding vertice %i: %f %f %f\n\n", v3, rawVertex[v3], rawVertex[v3+1], rawVertex[v3+2]);

	finalVertex[position]    = rawVertex[v1];
	finalVertex[position+1]  = rawVertex[v1+1];
	finalVertex[position+2]  = rawVertex[v1+2];

	finalVertex[position+3]  = rawVertex[v2];
	finalVertex[position+4]  = rawVertex[v2+1];
	finalVertex[position+5]  = rawVertex[v2+2];

	finalVertex[position+6]  = rawVertex[v3];
	finalVertex[position+7]  = rawVertex[v3+1];
	finalVertex[position+8]  = rawVertex[v3+2];

	/*
	   addVertice (&vertex, size, rawVertex[v1], rawVertex[v1+1], rawVertex[v1+2], position);
	   addVertice (&vertex, size, rawVertex[v2], rawVertex[v2+1], rawVertex[v2+2], position + 3);
	   addVertice (&vertex, size, rawVertex[v3], rawVertex[v3+1], rawVertex[v3+2], position + 6);

	   addNormal (normals, size, rawNormals[n1], rawNormals[n1+1], rawNormals[n1+2], position);
	   addNormal (normals, size, rawNormals[n2], rawNormals[n2+1], rawNormals[n2+2], position + 3);
	   addNormal (normals, size, rawNormals[n3], rawNormals[n3+1], rawNormals[n3+2], position + 6);

	   addTexCoord (tex, size, rawTexCoord[t1], rawTexCoord[t1+1], position);
	   addTexCoord (tex, size, rawTexCoord[t2], rawTexCoord[t2+1], position + 2);
	   addTexCoord (tex, size, rawTexCoord[t3], rawTexCoord[t3+1], position + 4);
	 */

#if MODEL_DEBUG
	//printf("nv%i: %f %f %f inserted at vertices[%i,%i,%i] and index %i f:%i v:%i\n",
	//		faces[f+v]+1, vertices[position], vertices[position+1], vertices[position+2],
	//		position, position+1, position+2, index, f, v);
	//printf("Face: % .3f % .3f % .3f at pos %li FCount:%li\n", x, y, z, position, model -> facesCount);
#endif
}


void initialize(const char* filePath, float scale)
{
	model.vertices = NULL;
	//model.faces = NULL;
	model.normals = NULL;
	model.texCoord = NULL;
	model.vertexCount = 0;
	//model.facesCount = 0;
	model.normalsCount = 0;
	model.textCoorCount = 0;
	model.scale = scale;

	if ((fptr = fopen(filePath, "r")) == NULL)
	{
		printf("Error while opening model file %s\n", filePath);
	}

	rawVertex 	= (GLfloat*) calloc (100, sizeof(GLfloat));
	rawNormals  = (GLfloat*) calloc (100, sizeof(GLfloat));
	rawTexCoord = (GLfloat*) calloc (100, sizeof(GLfloat));

	finalVertex   = (GLfloat*) calloc (100, sizeof(GLfloat));
	finalNormals  = (GLfloat*) calloc (100, sizeof(GLfloat));
	finalTexCoord = (GLfloat*) calloc (100, sizeof(GLfloat));

	if (rawVertex == NULL | rawNormals == NULL | rawTexCoord == NULL)
	{
		printf("Error while allocating memory in model.initialize\n");
	}
	printf("Initialization is over\n");
}


Model readModel (const char *filePath, float scale)
{
	initialize (filePath, scale);

	long vc = 0;
	long fc = 0;
	long nc = 0;
	long tc = 0;

	long vSize = 0;
	long nSize = 0;
	long tSize = 0;

	char *line = NULL;
	size_t len = 0;

	while (getline (&line, &len, fptr) != -1)
	{
		float x,y,z;
		int v1,v2,v3,t1,t2,t3,n1,n2,n3;
		char id[3];

		if (sscanf (line, "v%c %f %f %f\n", id, &x, &y, &z) > 0)
		{
			//printf("NOT A FACE! %s %f %f %f\n", id, x, y, z);
			if (strcmp(id, "t") == 0)
			{
				addTexCoord (&tSize, x, y, tc);
				tc++;
			}
			else if (strcmp(id, "n") == 0)
			{
				addNormal (&nSize, x, y, z, nc);
				nc++;
			}
			else 
			{
				addVertice (&vSize, x, y, z, vc);
				//printf("After: %f %f %f\n\n", rawVertex[0], rawVertex[1], rawVertex[2]);
				vc++;
			}

		}
		else if (sscanf (line, "f %i/%i/%i %i/%i/%i %i/%i/%i", 
					&v1,&t1,&n1,&v2,&t2,&n2,&v3,&t3,&n3) > 0)
		{
			//printf("A FACE!!!!!:  %s ", line);
			addFace (v1,v2,v3,n1,n2,n3,t1,t2,t3,fc,&vc);
			fc++;
		}
	}	

	//printf("%s\n", line);

	printf("Finished reading\n");
	/*model.vertexCount = vc;
	  model.vertices = (GLfloat*) realloc (model.vertices, sizeof(GLfloat) * model.vertexCount);
	//model.facesCount = fc;
	//model.faces = (GLuint*) realloc (model.faces, sizeof(GLuint) * model.facesCount);
	model.normalsCount = nc;
	model.normals = (GLfloat*) realloc (model.normals, sizeof(GLfloat) * model.normalsCount);
	model.textCoorCount = tc;
	model.texCoord = (GLfloat*) realloc (model.texCoord, sizeof(GLfloat) * model.textCoorCount);*/
#if MODEL_DEBUG
	//printf("Vertices: %li Faces: %li\n", model.vertexCount, model.facesCount);
#endif

	fclose(fptr);
	return model;	
}

void drawModel ()
{

	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);

	//glNormalPointer (GL_FLOAT, 0, normals);
	//glTextCoorPointer (2, GL_FLOAT, 0, textCoor);
	glVertexPointer (3, GL_FLOAT, 0, finalVertex);
	glDrawArrays(GL_TRIANGLES, 0, model.vertexCount);
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState (GL_NORMAL_ARRAY);
}
#endif
