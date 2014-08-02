#ifndef MODEL
#define MODEL

typedef struct model
{
	GLfloat *vertices;
    GLfloat *normals;
    GLfloat *texCoord;
	//GLuint *faces;
	GLint vCount;           // Vertices Count
    GLint nCount;
    GLint tCount;
	//GLint fCount;           // Faces Count
	GLfloat scale;
	GLfloat size;
} Model;

Model *model1;
Model *model2;
FILE *fptr;

GLfloat *rawVertices;
//GLfloat *normals;
//GLfloat *texCoord;

void addElement2f (GLfloat **list, GLint *size, float scale, float x, float y, GLint position)
{
	if (position >= *size - 2)
	{
		*size += 100;
		*list = (GLfloat*) realloc (*list, sizeof(GLfloat) * (*size));
		if (list == NULL)
		{
			printf("Error trying to reallocate memory\n");
		}
	}
	(*list)[position]   = (GLfloat) x;
	(*list)[position+1] = (GLfloat) y;
#if MODEL_DEBUG
	printf("TexCoord: % .3f % .3f at pos %i Count:%i\n", x, y, position, *size);
#endif
}

void addElement3f (GLfloat **list, GLint *size, float scale, float x, float y, float z, GLint position)
{
    int index = position * 3;
    if (index >= *size - 3)
	{
		*size += 100;
		*list = (GLfloat*) realloc (*list, sizeof(GLfloat) * (*size));
		if (*list == NULL)
		{
			printf("Error trying to reallocate memory\n");
		}
	}
	(*list)[index]   = (GLfloat) x * scale;
	(*list)[index+1] = (GLfloat) y * scale;
    (*list)[index+2] = (GLfloat) z * scale;
    
#if MODEL_DEBUG
	printf("Ver: % .3f % .3f % .3f at pos %i Size:%i\n", x, y, z, index, *size);
#endif
}

void addFace (Model *model, GLint *size, int v1, int v2, int v3, GLint position)
{
    printf("Setting face %i size: %i v1: %i v2: %i v3: %i\n", position, *size, v1, v2, v3);
    
    if (position == 0)
    {
        
        model -> vertices = (GLfloat*) calloc(*size * 3, sizeof(GLfloat));
    }
    
    v1 = (v1 - 1) * 3;
    v2 = (v2 - 1) * 3;
    v3 = (v3 - 1) * 3;
    
    model -> vertices[position]    = rawVertices[v1];
	model -> vertices[position+1]  = rawVertices[v1+1];
	model -> vertices[position+2]  = rawVertices[v1+2];
    
	model -> vertices[position+3]  = rawVertices[v2];
	model -> vertices[position+4]  = rawVertices[v2+1];
	model -> vertices[position+5]  = rawVertices[v2+2];
    
	model -> vertices[position+6]  = rawVertices[v3];
	model -> vertices[position+7]  = rawVertices[v3+1];
	model -> vertices[position+8]  = rawVertices[v3+2];
    
    printf("Value of v1: %i v2: %i v3: %i\n", v1, v2, v3);
    printf("Face %i has elements \n\tv1: %f %f %f \n\tv2: %f %f %f \n\tv3: %f %f %f\n",
           position,
           model -> vertices[position],
           model -> vertices[position+1],
           model -> vertices[position+2],
           model -> vertices[position+3],
           model -> vertices[position+4],
           model -> vertices[position+5],
           model -> vertices[position+6],
           model -> vertices[position+7],
           model -> vertices[position+8]);
    
    
#if MODEL_DEBUG
	//printf("Face: % % .3f % .3f at pos %li FCount:%li\n", x, y, z, position, *size);
#endif
}

void initialize (Model *model, const char* filePath, GLfloat scale)
{
    if ((fptr = fopen(filePath, "r")) == NULL)
	{
		printf("Error while opening file %s\n", filePath);
	}
    
    //model -> vertices = NULL;
    //model -> normals = NULL;
    //model -> texCoord = NULL;
	//model -> faces = NULL;
	model -> vCount = 0;
    model -> nCount = 0;
    model -> tCount = 0;
	//model -> fCount = 0;
	model -> scale = scale;
	model -> size = 0;
    model -> vertices= NULL;
    rawVertices = (GLfloat*) calloc (100, sizeof(GLfloat));
    
	printf("Initialization for %s is over\n", filePath);
}

Model* readModel (const char *filePath, GLfloat scale)
{
	Model *model = (Model*) malloc (sizeof(Model));
    initialize(model, filePath, scale);
	
    GLint vc = 0;
    //GLint nc = 0;
    //GLint tc = 0;
    GLint fc = 0;
    GLint vSize = 0;
    
    char *line = NULL;
    size_t len = 0;
    
    while (getline (&line, &len, fptr) != -1)
	{
       
        GLfloat x,y,z;
        int v1,v2,v3,n1,n2,n3,t1,t2,t3;
        //char id[3];
        
        if (sscanf (line, "v %f %f %f\n", &x, &y, &z) > 0)
		{
            addElement3f(&rawVertices, &vSize, model -> scale, x, y, z, vc);
            vc++;
        }
        else if (sscanf (line, "f %i/%i/%i %i/%i/%i %i/%i/%i",
                         &v1,&t1,&n1,&v2,&t2,&n2,&v3,&t3,&n3) > 0)
        {
            //if (fc < 9)
            //{
                //printf("FACE at line %i %i/%i/%i %i/%i/%i %i/%i/%i\n", lineC, v1,n1,t1,v2,n2,t2,v3,n3,t3);
                addFace(model, &vc, v1, v2, v3, fc);
                fc++;
            //}
        }
    }
    model -> vCount = vc;
    model -> vertices = (GLfloat*) realloc (model -> vertices, sizeof(GLfloat) * model -> vCount);
    printf("Finished loading model %s\n\n\n\n\n", filePath);
    fclose(fptr);
    return model;
}

void drawModel (Model *model, vec3 position)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, model -> vertices);
    glDrawArrays(GL_TRIANGLES, 0, model -> vCount);
    glDisableClientState(GL_VERTEX_ARRAY);
}
#endif
