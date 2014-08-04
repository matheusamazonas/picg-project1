// --------------- model.hpp ----------------||
//         Author: Matheus A C de Andrade    ||
// Model loading and rendering. I don't want ||
// to scare anyone, but modify this file only||
// if you really know what you're doing. Most||
// of the implementation time was spent here.||
// ------------------------------------------||

#ifndef MODEL
#define MODEL

// A model consists of its vertices (points), normals (say how light
//  will affect that face) and the texture mapping.
typedef struct model
{
	GLfloat *vertices;
    GLfloat *normals;
    GLfloat *texCoords;
	GLint vCount;
    GLint nCount;
    GLint tCount;
	GLfloat scale;
	GLfloat size;
    GLuint texture;
} Model;

// File pointer used to load the model files (.obj)
FILE *fptr;
// The models shared through the application. Even though there are
//  several objects, all the objects from the same model shares the
//  model struct with the others. Because, you know, memory.
Model *model1;
Model *model2;

// The raw data for all the model elements. First note that only here
//  we have the faces. That's because they are not sent to the OpenGL
//  Draw call. They are useful only to reorganize the other elements
//  to their correct order. After that, the faces are useless. Second
//  remember that the elements in the model file are not in the order
//  they should be sent to the OpenGL Draw call. They are in the most
//  condensed and smallest representation possible.
GLfloat *rawVertices;
GLint *rawFaces;
GLfloat *rawNormals;
GLfloat *rawTexCoords;

void processData (Model *model, GLint size, int tCount);

// Addes 3 floats elements to the given list and increases its size if
//  needed. It really adds a vector3 (x,y,z). used to add vertices,
//  texture coordinates (they are 3f in the .obj file) and normals.
void addElement3f (GLfloat **list, GLint *size, float scale, float x, float y, float z, GLint position)
{
    int index = position * 3;
    if (index >= *size - 3)
	{
		*size += 100;
		*list = (GLfloat*) realloc(*list, sizeof(GLfloat) * (*size));
		if (*list == NULL)
		{
			printf("Error trying to reallocate memory in addElement3f\n");
		}
	}
	(*list)[index]   = (GLfloat) x * scale;
	(*list)[index+1] = (GLfloat) y * scale;
    (*list)[index+2] = (GLfloat) z * scale;
    
#if MODEL_DEBUG
	printf("Added element: % .3f % .3f % .3f at pos %i Size:%i\n", x, y, z, index, *size);
#endif
}

// Addes a face to the faces list and increases its size if needed. Remember
//  that each face has 3 vertices, 3 normals and 3 texture coordinates
void addFace (GLint **faces, GLint *size, int v1, int v2, int v3, int n1, int n2, int n3, int t1, int t2, int t3 ,GLint position)
{
    int index = position * 9;
    if (index >= *size - 9)
	{
		*size += 900;
		*faces = (GLint*) realloc(*faces, sizeof(GLint) * (*size));
		if (*faces == NULL)
		{
			printf("Error trying to reallocate memory in addFace\n");
		}
	}
	(*faces)[index]     = v1;
    (*faces)[index+1]   = n1;
    (*faces)[index+2]   = t1;
	(*faces)[index+3]   = v2;
    (*faces)[index+4]   = n2;
    (*faces)[index+5]   = t2;
    (*faces)[index+6]   = v3;
    (*faces)[index+7]   = n3;
    (*faces)[index+8]   = t3;
    
#if MODEL_DEBUG
	printf("Face at pos %i Size:%i v1:%i v2:%i v3:%i ", position, *size, v1, v2, v3);
    printf("n1:%i n2:%i n3:%i\n", n1, n2, n3);
#endif
}

// Initializes a model. Open its file and check for erros, allocates memory
//  to the raw components, and initializes variables and components
void initialize (Model *model, const char* filePath, GLfloat scale)
{
    if ((fptr = fopen(filePath, "r")) == NULL)
	{
		printf("Error while opening file %s\n", filePath);
        exit(-1);
	}
    
    model -> vertices = NULL;
    model -> normals = NULL;
    model -> texCoords = NULL;
	model -> vCount = 0;
    model -> nCount = 0;
    model -> tCount = 0;
	model -> scale = scale;
	model -> size = 0;
    // Allocates for the RAW elements
    rawVertices  = (GLfloat*) calloc(100, sizeof(GLfloat));
    rawNormals   = (GLfloat*) calloc(100, sizeof(GLfloat));
    rawTexCoords = (GLfloat*) calloc(100, sizeof(GLfloat));
    rawFaces = (GLint*) calloc (100, sizeof(GLint));
#if MODEL_DEBUG
	printf("Initialization for %s is over\n", filePath);
#endif
}

// The reading model function itself. Loads a model located on the given
//  path and scales it by the given factor
//                  **** MAGIC HERE ****
Model* readModel (const char *filePath, GLfloat scale)
{
	Model *model = (Model*) malloc(sizeof(Model));
    initialize(model, filePath, scale);
	
    // Auxiliar variables used to read the model
    GLint vc = 0;
    GLint nc = 0;
    GLint tc = 0;
    GLint fc = 0;
    GLint vSize = 0;
    GLint nSize = 0;
    GLint tSize = 0;
    GLint fSize = 0;
    
    // Each fiel's line is placed in this variable
    char *line = NULL;
    size_t len = 0;
    
    while (getline (&line, &len, fptr) != -1)
	{
        
        GLfloat x,y,z;
        int v1,v2,v3,n1,n2,n3,t1,t2,t3;
        char id;
        
        // Reads each line and check its type (vertice, normal, texture coordinates
        //  or face, calls its correspondent add function and updates its counter
        if (sscanf (line, "v%c %f %f %f\n", &id, &x, &y, &z) > 0)
		{
            if (id == ' ')
            {
                addElement3f(&rawVertices, &vSize, model -> scale, x, y, z, vc);
                vc++;
            }
            if (id == 'n')
            {
                addElement3f(&rawNormals, &nSize, 1.0f, x, y, z, nc);
                nc++;
            }
            if (id == 't')
            {
                y = 1 - y;
                addElement3f(&rawTexCoords, &tSize, 1.0f, x, y, z, tc);
                tc++;
            }
        }
        else if (sscanf (line, "f %i/%i/%i %i/%i/%i %i/%i/%i",
                         &v1,&t1,&n1,&v2,&t2,&n2,&v3,&t3,&n3) > 0)
        {
            addFace(&rawFaces, &fSize, v1, v2, v3, n1, n2, n3, t1, t2, t3, fc);
            fc++;
        }
    }
    // Proccess the Models's data. This is big.
    processData(model, fc, tc);
#if MODEL_DEBUG
	printf("vCount: %i\n", model -> vCount);
    printf("Finished loading model %s\n\n", filePath);
#endif
    // Frees memory and closes the model file
    free(rawVertices);
    free(rawNormals);
    free(rawTexCoords);
    free(rawFaces);
    fclose(fptr);
    return model;
}

// This is where most of the model processing is done. This is the
//  complicated part. Based on the faces, the components are copied
//  to the finao model array. The logic behind this is basically the
//  OBJ file organization explanation. This is the function that most
//  of the implementation was done and the tiniest change here may
//  affect the whole application rendering dramatically. So change
//  stuff here if you really know what you're doing
void processData (Model *model, GLint size, int tCount)
{
    model -> vertices  = (GLfloat*) calloc(size * 9, sizeof(GLfloat));
    model -> normals   = (GLfloat*) calloc(size * 9, sizeof(GLfloat));
    model -> texCoords = (GLfloat*) calloc(size * 9, sizeof(GLfloat));
    
    model -> vCount = size * 3;
    model -> nCount = size * 3;
    model -> tCount = size * 3;
    
    for (int position = 0; position < size*9; position += 9)
    {
        int v1 = rawFaces[position];
        int v2 = rawFaces[position+3];
        int v3 = rawFaces[position+6];
        
        int n1 = rawFaces[position+1];
        int n2 = rawFaces[position+4];
        int n3 = rawFaces[position+7];
        
        int t1 = rawFaces[position+2];
        int t2 = rawFaces[position+5];
        int t3 = rawFaces[position+8];
        
#if MODEL_DEBUG
        printf("Processing data at %i v1: %i v2: %i v3: %i\n", position, v1, v2, v3);
        printf("Processing data at %i n1: %i n2: %i n3: %i\n", position, n1, n2, n3);
        printf("Processing data at %i t1: %i t2: %i t3: %i\n", position, t1, t2, t3);
#endif
        
        v1 = (v1 - 1) * 3;
        v2 = (v2 - 1) * 3;
        v3 = (v3 - 1) * 3;
        
        n1 = (n1 - 1) * 3;
        n2 = (n2 - 1) * 3;
        n3 = (n3 - 1) * 3;
        
        t1 = (t1 - 1) * 3;
        t2 = (t2 - 1) * 3;
        t3 = (t3 - 1) * 3;
        
        model -> vertices[position]    = rawVertices[v1];
        model -> vertices[position+1]  = rawVertices[v1+1];
        model -> vertices[position+2]  = rawVertices[v1+2];
        
        model -> vertices[position+3]  = rawVertices[v2];
        model -> vertices[position+4]  = rawVertices[v2+1];
        model -> vertices[position+5]  = rawVertices[v2+2];
        
        model -> vertices[position+6]  = rawVertices[v3];
        model -> vertices[position+7]  = rawVertices[v3+1];
        model -> vertices[position+8]  = rawVertices[v3+2];
        
        model -> normals[position]    = rawNormals[n1];
        model -> normals[position+1]  = rawNormals[n1+1];
        model -> normals[position+2]  = rawNormals[n1+2];
        
        model -> normals[position+3]  = rawNormals[n2];
        model -> normals[position+4]  = rawNormals[n2+1];
        model -> normals[position+5]  = rawNormals[n2+2];
        
        model -> normals[position+6]  = rawNormals[n3];
        model -> normals[position+7]  = rawNormals[n3+1];
        model -> normals[position+8]  = rawNormals[n3+2];
        
        model -> texCoords[position]    = rawTexCoords[t1];
        model -> texCoords[position+1]  = rawTexCoords[t1+1];
        model -> texCoords[position+2]  = rawTexCoords[t1+2];
        
        model -> texCoords[position+3]  = rawTexCoords[t2];
        model -> texCoords[position+4]  = rawTexCoords[t2+1];
        model -> texCoords[position+5]  = rawTexCoords[t2+2];
        
        model -> texCoords[position+6]  = rawTexCoords[t3];
        model -> texCoords[position+7]  = rawTexCoords[t3+1];
        model -> texCoords[position+8]  = rawTexCoords[t3+2];
    }
}

// Draw the given model at the given position. Since some room elements
//  share the same model, we need to run through the vertices to update
//  its  position with the element's position (2nd argument)
void drawModel (Model *model, vec3 position)
{
    GLfloat *vertices = (GLfloat*) calloc(model -> vCount*3, sizeof(GLfloat));
    for (int i = 0; i < model -> vCount*3; i += 3)
    {
        vertices[i]   = model -> vertices[i] + position.x;
        vertices[i+1] = model -> vertices[i+1] + position.y;
        vertices[i+2] = model -> vertices[i+2] + position.z;
    }
    
    // All OpenGL calls to set the model drawing
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, model -> texture);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glTexCoordPointer(3, GL_FLOAT, 0, model -> texCoords);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, model -> normals);
    
    glDrawArrays(GL_TRIANGLES, 0, model -> vCount);
    
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_2D);
    // This call is extremelly important and its deletion can result in serious
    //  memory leak
    free(vertices);
}
#endif
