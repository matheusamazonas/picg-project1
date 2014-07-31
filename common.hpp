#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "glm/glm.hpp"
using namespace glm;

#define GLM_FORCE_RADIANS

#define MAIN_DEBUG 		0
#define WALL_DEBUG 		0
#define ROOM_DEBUG 		0
#define GRID_DEBUG 		0
#define MODEL_DEBUG 	0
#define TEXTURE_DEBUG 	1

#define LIGHT 			0

#define IMAGE_HEIGHT 128
#define IMAGE_WIDTH 128

#ifndef TEXTURE
#include "texture.hpp"
#endif

#ifndef WALL
#include "wall.hpp"
#endif

#ifndef ROOM
#include "room.hpp"
#endif

#ifndef GRID
#include "grid.hpp"
#endif

#ifndef MODEL
#include "model.hpp"
#endif


