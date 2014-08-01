#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;

#ifndef TEXTURE
#define TEXTURE

GLuint tex;
int width, height;
unsigned char* image;
const char* texName = "textures/texture.bmp";

void configTextMode()
{
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, grassText);
	glGenTextures(1, &tex);

	image = SOIL_load_image (texName, &width, &height, 0, SOIL_LOAD_RGB);
	if( 0 == tex)
	{
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);


	//como a textura será tratada se não há mapeamento direto 
	//entre pixels e coordenadas de textura (GL_REPEAT ou GL_CLAMP)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//magnification e minification filters
	//GL_NEAREST: texel com coordenadas mais próximas do centro do pixel 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

#endif
