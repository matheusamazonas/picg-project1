#ifndef MODEL
#define MODEL

#define MODEL_DEBUG 0

#include <string>
#include <stdio.h>
using namespace std;

typedef struct model
{
	GLfloat *vertices; 
	GLuint *faces;
	long vertexCount;
	long facesCount;
} Model;


void addFace (Model *model, float x, float y, float z, long position)
{
	GLuint *fac = model -> faces;
	
	if (position >= model -> facesCount - 3)
	{
		model -> facesCount += 100;
		fac = (GLuint*) realloc (fac, sizeof(GLuint) * (model -> facesCount));
		if (fac == NULL)
		{
			printf("Error trying to reallocate memory\n");
		}
		else
		{
			model -> faces = fac;
		}
	}
	fac[position]   = (GLuint) x;
	fac[position+1] = (GLuint) y;
	fac[position+2] = (GLuint) z;
#if MODEL_DEBUG
	printf("Face: % .3f % .3f % .3f at pos %li FCount:%li\n", x, y, z, position, model -> facesCount);
#endif
}


void addVertice (Model *model, float x, float y, float z, long position)
{
	GLfloat *ver = model -> vertices;

	if (position >= model -> vertexCount - 3)
	{
		model -> vertexCount += 100;
		ver = (GLfloat*) realloc (ver, sizeof(GLfloat) * (model -> vertexCount));
		if (ver == NULL)
		{
			printf("Error trying to reallocate memory\n");
		}
		else
		{
			model -> vertices = ver;
		}
	}
	ver[position]   = (GLfloat) x;
	ver[position+1] = (GLfloat) y;
	ver[position+2] = (GLfloat) z;
#if MODEL_DEBUG
	printf("Ver: % .3f % .3f % .3f at pos %li VCount:%li\n", x, y, z, position, model -> vertexCount);
#endif
}


Model readModel (const char *filePath)
{
	Model model;
	model.vertices = NULL;
	model.faces = NULL;
	model.vertexCount = 0;
	model.facesCount = 0;

	FILE *fptr;

	if ((fptr = fopen(filePath, "r")) == NULL)
	{
		printf("Error while opening file %s\n", filePath);
	}
	else
	{
		long vc = 0;
		long fc = 0;
		float x,y,z;
		char id[3];

		model.vertices = (GLfloat*) calloc (100, sizeof(GLfloat));
		model.faces	   = (GLuint*) calloc (100, sizeof(GLuint));
		while (fscanf (fptr, "%s %f %f %f\n", id, &x, &y, &z) != EOF)
		{
			if (strcmp(id, "v") == 0)
			{
				addVertice (&model, x, y, z, vc);
				vc += 3;
			}
			else if (strcmp(id, "f") == 0)
			{
				addFace (&model, x, y, z, fc);
				fc += 3;
			}
		}
		model.vertexCount = vc;
		model.vertices = (GLfloat*) realloc (model.vertices, sizeof(GLfloat) * model.vertexCount);
		model.facesCount = fc;
		model.faces = (GLuint*) realloc (model.faces, sizeof(GLuint) * model.facesCount);
#if MODEL_DEBUG
		printf("Vertices: %li Faces: %li\n", model.vertexCount, model.facesCount);
#endif
	}

	fclose(fptr);
	return model;	
}

void drawModel (Model model)
{
	/*
	GLfloat *vertices = model.vertices;	

	glVertexPointer (3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	*/

}	
#endif
