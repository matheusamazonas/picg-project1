#ifndef MODEL
#define MODEL

typedef struct model
{
	GLfloat *vertices; 
	GLuint *faces;
	GLint vCount;           // Vertices Count
	GLint fCount;           // Faces Count
	GLfloat scale;
	GLfloat size;
} Model;

Model *model1;
Model *model2;

void addFace (GLuint **fac, int *size, float scale, float x, float y, float z, long position)
{
	if (position >= *size - 3)
	{
		*size += 100;
		*fac = (GLuint*) realloc (*fac, sizeof(GLuint) * (*size));
		if (fac == NULL)
		{
			printf("Error trying to reallocate memory\n");
		}
	}
	(*fac)[position]   = (GLuint) x;
	(*fac)[position+1] = (GLuint) y;
	(*fac)[position+2] = (GLuint) z;
#if MODEL_DEBUG
	printf("Face: % .3f % .3f % .3f at pos %li FCount:%li\n", x, y, z, position, model -> facesCount);
#endif
}


void addVertice (GLfloat **ver, int *size, float scale, float x, float y, float z, long position)
{
    if (position >= *size - 3)
	{
		*size += 100;
		*ver = (GLfloat*) realloc (*ver, sizeof(GLfloat) * (*size));
		if (*ver == NULL)
		{
			printf("Error trying to reallocate memory\n");
		}
	}
	(*ver)[position]   = (GLfloat) x * scale;
	(*ver)[position+1] = (GLfloat) y * scale;
    (*ver)[position+2] = (GLfloat) z * scale;
    
#if MODEL_DEBUG
	printf("Ver: % .3f % .3f % .3f at pos %li VCount:%li\n", x, y, z, position, model -> vertexCount);
#endif
}

Model* readModel (const char *filePath, float scale)
{
	Model *model = (Model*) malloc (sizeof(Model)); 
	model -> vertices = NULL;
	model -> faces = NULL;
	model -> vCount = 0;
	model -> fCount = 0;
	model -> scale = scale;
	model -> size = 0;

	FILE *fptr;

	if ((fptr = fopen(filePath, "r")) == NULL)
	{
		printf("Error while opening file %s\n", filePath);
	}
	else
	{
		GLuint vc = 0;
		GLuint fc = 0;
		GLfloat x,y,z;
		char id[3];
        
		model -> vertices = (GLfloat*) calloc (100, sizeof(GLfloat));
		model -> faces	   = (GLuint*) calloc (100, sizeof(GLuint));
        
		while (fscanf (fptr, "%s %f %f %f\n", id, &x, &y, &z) != EOF)
		{
			if (strcmp(id, "v") == 0)
			{
				addVertice (&model -> vertices, &model -> vCount, model -> scale, x, y, z, vc);
				vc += 3;
			}
			else if (strcmp(id, "f") == 0)
			{
				addFace (&model -> faces, &model -> fCount, model -> scale, x, y, z, fc);
				fc += 3;
			}

		}
		model -> vCount = vc;
		model -> vertices = (GLfloat*) realloc (model -> vertices, sizeof(GLfloat) * model -> vCount);
		model -> fCount = fc;
		model -> faces = (GLuint*) realloc (model -> faces, sizeof(GLuint) * model -> fCount);

#if MODEL_DEBUG
		printf("Vertices: %li Faces: %li\n", model -> vertexCount, model -> facesCount);
#endif
	}

	fclose(fptr);
	return model;	
}

void drawModel (Model *model, vec3 position)
{
	GLuint vCount = model -> fCount * 3;
	GLfloat vertices[vCount];
	GLuint *faces = model -> faces;

	glEnableClientState(GL_VERTEX_ARRAY);

	for (int f = 0; f < model -> fCount; f += 3)
	{
#if MODEL_DEBUG
		printf("Preparing face face: %i\n", f);
#endif
		for (int v = 0; v < 3; v++)
		{
			int index = (faces[f+v]-1) * 3;
			int p = (f+v) * 3;
			vertices[p]   = model -> vertices[index]   + position.x;
			vertices[p+1] = model -> vertices[index+1] + position.y;
			vertices[p+2] = model -> vertices[index+2] + position.z;
#if MODEL_DEBUG
			printf("nv%i: %f %f %f inserted at vertices[%i,%i,%i] and index %i f:%i v:%i\n",
					faces[f+v]+1, vertices[p], vertices[p+1], vertices[p+2],
					p, p+1, p+2, index, f, v);
#endif			
		}
	}
	glVertexPointer (3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, model -> fCount);
	glDisableClientState(GL_VERTEX_ARRAY);
}
#endif
