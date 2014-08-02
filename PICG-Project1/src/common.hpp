#include <stdio.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <SOIL.h>

#define GLM_FORCE_RADIANS
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

using namespace glm;
using namespace std;

#define MAIN_DEBUG 		  0
#define WALL_DEBUG 		  0
#define ROOM_DEBUG 		  0
#define GRID_DEBUG 		  0
#define MODEL_DEBUG 	  0
#define TEXTURE_DEBUG 	  0
#define INPUT_DEBUG       0
#define LIGHT 			  0

GLuint windowSizeX        = 800, windowSizeY = 600;
GLfloat camSpeed 		  = 0.2f;
GLfloat mouseSpeed        = 0.0055f;
GLfloat roomSize 		  = 2.0f;
GLfloat model1Scale       = 0.3f;
GLfloat model2Scale       = 0.05f;
GLfloat model1Size        = 5.0f;
GLfloat model2Size        = 1.0f;

const char* texName       = "textures/texture.bmp";
const char* model1Path    = "models/teapot.obj";
const char* model2Path    = "models/teddy.obj";

GLfloat horizontalAngle   = 3.14f;
GLfloat verticalAngle     = 0.0f;
GLfloat deltaTime;

vec3 cameraPos = vec3(0.0f, 2.0f, -10.0f);
vec3 cameraTarget = vec3(0.0f, 0.0f, 1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

GLFWwindow* window;

#ifndef TEXTURE
#include "texture.hpp"
#endif

#ifndef WALL
#include "wall.hpp"
#endif

#ifndef MODEL
#include "model.hpp"
#endif

#ifndef OBJECT
#include "object.hpp"
#endif

#ifndef ROOM
#include "room.hpp"
#endif

#ifndef GRID
#include "grid.hpp"
#endif

#ifndef INPUT
#include "input.hpp"
#endif
