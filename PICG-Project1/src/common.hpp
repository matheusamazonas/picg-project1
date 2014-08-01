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

#define MAIN_DEBUG 		0
#define WALL_DEBUG 		0
#define ROOM_DEBUG 		0
#define GRID_DEBUG 		0
#define MODEL_DEBUG 	0
#define TEXTURE_DEBUG 	0
#define INPUT_DEBUG     0

#define LIGHT 			0

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

GLuint windowSizeX    = 800, windowSizeY = 600;
GLfloat camSpeed 		  = 0.2f;
GLfloat mouseSpeed 	  = 0.0055f;
GLfloat roomSize 		  = 2.0f;

GLfloat horizontalAngle = 3.14f;
GLfloat verticalAngle   = 0.0f;
GLfloat deltaTime;



