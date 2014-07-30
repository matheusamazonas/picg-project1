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
	GLfloat *normals;
	long vertexCount;
	long facesCount;
	long normalCount;
	float scale;
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
	
	ver[position]   = (GLfloat) x * model -> scale;
	ver[position+1] = (GLfloat) y * model -> scale;
	ver[position+2] = (GLfloat) z * model -> scale;
#if MODEL_DEBUG
	printf("Ver: % .3f % .3f % .3f at pos %li VCount:%li\n", x, y, z, position, model -> vertexCount);
#endif
}


Model readModel (const char *filePath, float scale)
{
	Model model;
	model.vertices = NULL;
	model.faces = NULL;
	model.normals = NULL;
	model.vertexCount = 0;
	model.facesCount = 0;
	model.normalCount = 0;
	model.scale = scale;

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
		model.normals  = (GLfloat*) calloc (100, sizeof(GLfloat));
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
	int vCount = model.facesCount*3;
	GLfloat vertices[vCount];
	GLuint *faces = model.faces;
	GLfloat normals[model.facesCount];
	
	glEnableClientState(GL_NORMAL_ARRAY);

	for (int f = 0; f < model.facesCount; f += 3)
	{
#if MODEL_DEBUG
		printf("Preparing face face: %i\n", f);
#endif
		for (int v = 0; v < 3; v++)
		{
			int index = (faces[f+v]-1) * 3;
			int position = (f+v) * 3;
			vertices[position]   = model.vertices[index];
			vertices[position+1] = model.vertices[index+1];
			vertices[position+2] = model.vertices[index+2];
#if MODEL_DEBUG
			printf("nv%i: %f %f %f inserted at vertices[%i,%i,%i] and index %i f:%i v:%i\n",
					faces[f+v]+1, vertices[position], vertices[position+1], vertices[position+2],
					position, position+1, position+2, index, f, v);
#endif			
		}
		int index = 3*f;
		vec3 v1 = vec3 (vertices[index], vertices[index+1], vertices[index+2]);
		vec3 v2 = vec3 (vertices[index+3], vertices[index+4], vertices[index+5]);
		vec3 v3 = vec3 (vertices[index+6], vertices[index+7], vertices[index+8]);
		
		vec3 normal = normalize(cross(v3 - v1, v2 - v1));
		normals[f] = normal.x;
		normals[f+1] = normal.y;
		normals[f+2] = normal.z;
	}
	glNormalPointer (GL_FLOAT, 0, normals);
	glVertexPointer (3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, model.facesCount);
}
#endif
