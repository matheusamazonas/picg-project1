#include <stdio.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include "../include/SOIL.h"
#include "../include/glm/glm.hpp"

using namespace glm;
using namespace std;

#define GLM_FORCE_RADIANS

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

double windowSizeX    = 800, windowSizeY = 600;
float camSpeed 		  = 0.2f;
float mouseSpeed 	  = 0.0055f;
float roomSize 		  = 2.0f;

float horizontalAngle = 3.14f;	   	
float verticalAngle   = 0.0f;		
float deltaTime;



