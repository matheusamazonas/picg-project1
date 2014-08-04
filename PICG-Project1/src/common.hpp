// --------------- common.hpp ---------------||
//         Author: Matheus A C de Andrade    ||
//          Common imports / definitions     ||
// ------------------------------------------||

// List of libraries used
// GLFW3: User input and window management
// OpenGL: Graphics Library
// SOIL: loading files (BMP to texture)
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <SOIL.h>
#include <string>
#include <stdio.h>

// GLM is a Mathematic Self-Contained Library, so we need
//  to include it statically
#define GLM_FORCE_RADIANS
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

using namespace glm;
using namespace std;

// Debug flags session. Activating all the flags may slow
//  down your the application
#define MAIN_DEBUG 		  0
#define WALL_DEBUG 		  0
#define ROOM_DEBUG 		  0
#define GRID_DEBUG 		  0
#define MODEL_DEBUG 	  0
#define TEXTURE_DEBUG 	  0
#define INPUT_DEBUG       0

// Window initial size. The window may be resized, but the
//  aspect will change accordingly
GLuint windowSizeX        = 800,
       windowSizeY        = 600;

// Cam speed (movement speed) and boost
// Press Left Shift to boost speed!
GLfloat camSpeed 		  = 0.2f;
GLfloat speedBoost        = 1.0f;

// Mouse speed (looking around)
GLfloat mouseSpeed        = 0.0055f;

// Room default size (nxn) and maximum numbers of rooms the
//  application will accept
GLfloat roomSize 		  = 50.0f;
GLint   maxRooms          = 10;
GLfloat planeSize         = 1000.0f;

// Model scaling and size. Note that the only the scaling will
//  affect the object's size. The size variable is used only
//  to compute how many objects cann be placed  in a room
GLfloat model1Scale       = 0.05f;
GLfloat model2Scale       = 4.0f;
GLfloat model1Size        = 7.0f;
GLfloat model2Size        = 1.0f;
GLint largeObjectSize     = 1.0f;

// Light switch controled by the key L
bool light                = true;

// Textures and 3D models paths. Note that even though the
//  paths are relative to the executable, you need to copy
//  them to the build path when running it in XCode
const char* roomTexPath   = "textures/texture.bmp";
const char* model1Path    = "models/dog.obj";
const char* model1TexPath = "textures/dog.bmp";
const char* model2Path    = "models/cat.obj";
const char* model2TexPath = "textures/cat.bmp";

// Angles and time used to calculate mouse movement
GLfloat horizontalAngle   = 3.14f;
GLfloat verticalAngle     = 0.0f;
GLfloat deltaTime;

// Camera's position, target and up vectors
vec3 cameraPos = vec3(0.0f, 30.0f, 40.0f);
vec3 cameraTarget = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

// The only window the application has
GLFWwindow* window;

// List of includes. Keep the order to don't mess things up
#ifndef MODEL
#include "model.hpp"
#endif

#ifndef TEXTURE
#include "texture.hpp"
#endif

#ifndef WALL
#include "wall.hpp"
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