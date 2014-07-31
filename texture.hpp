#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;

#ifndef TEXTURE
#define TEXTURE

GLuint grassTextName;
GLchar grassImage[IMAGE_HEIGHT][IMAGE_WIDTH][4];
//const char* grassName = "textures/grass.jpg";
const char* grassName = "textures/test.txt";

//Source: http://www.cplusplus.com/forum/beginner/25307/
void loadTexture (GLchar texture[128][128][4], const char *textName)
{
	ifstream ifs;
	ifs.open(textName, ios::in | ios::binary);
	ostringstream oss;
	//printf("Text path %s and syze %i is open? %i\n", textName, ifs.get(), ifs.is_open());

	int len;
	char buffer[128];

	/*while ((len = ifs.readsome (buffer, 128)) > 0)
	  {
	  printf("Just read %i\n", len);
	  oss.write(buffer, len);
	  }*/
	//printf("Len: %i\n", len);	
	//const char* data = oss.str().c_str();
	for (int i = 0; i < IMAGE_HEIGHT; i++) 
	{
		//for (int j = 0; j < IMAGE_WIDTH; j++)
		for (int j = 0; j < 1; j++) 
		{
			printf("Reading %i %i", i, j);
			texture[i][j][0] = ifs.get();
			texture[i][j][1] = ifs.get();
			texture[i][j][2] = ifs.get();
			texture[i][j][3] = (GLchar) 255;
			printf(" r:%c g:%c b:%c %c\n",
					texture[i][j][0],
					texture[i][j][1],
					texture[i][j][2],
					texture[i][j][3]);
			//int index = (i*4) + j;
			//texture[i][j][0] = data[index];
			//texture[i][j][1] = data[index+1];
			//texture[i][j][2] = data[index+2];
			//texture[i][j][3] = (GLchar) 255;
		}
	}
	printf("Finished reading\n");	
}	

void configTextMode()
{
	// Carrega a textura do arquivo
	loadTexture (grassImage, grassName);
	//declara um objeto de textura
	glGenTextures (1, &grassTextName);
	//cria e usa objetos de textura 
	//podem ser trocados ou removidos (remoção: texName=0)
	glBindTexture(GL_TEXTURE_2D, grassTextName);
	//como a textura será tratada se não há mapeamento direto 
	//entre pixels e coordenadas de textura (GL_REPEAT ou GL_CLAMP)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//magnification e minification filters
	//GL_NEAREST: texel com coordenadas mais próximas do centro do pixel 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//define uma textura bidimensional
	/*void glTexImage2D(
	 * GLenum target, 
	 * GLint level, 
	 * GLint internalFormat, (número de componentes)
	 * GLsizei width, 
	 * GLsizei height, 
	 * GLint border,
	 * GLenum format, 
	 * GLenum type,    (tipos dos dados)
	 * const GLvoid *pixels);*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, IMAGE_WIDTH, 
			IMAGE_HEIGHT, 0, GL_RGBA, GL_BYTE, grassImage);	
}
 
#endif
