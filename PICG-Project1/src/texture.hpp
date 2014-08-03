#ifndef TEXTURE
#define TEXTURE

GLuint texNames[3];
GLint width, height;
unsigned char* roomImage;
unsigned char* model1Image;
unsigned char* model2Image;

void configTextMode ()
{
	glGenTextures(3, texNames);
    
    
    // Texture0 - Room Texture
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    roomImage = SOIL_load_image(roomTexPath, &width, &height, 0, SOIL_LOAD_RGB);
	if(0 == texNames[0])
	{
		printf("SOIL loading error: '%s' while trying to load file %s\n", SOIL_last_result(), roomTexPath );
        exit(-1);
	}
    SOIL_free_image_data(roomImage);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, roomImage);

    
    
    
    // Texture1 - Model1's Texture
    glBindTexture(GL_TEXTURE_2D, texNames[1]);
    model1Image = SOIL_load_image(model1TexPath, &width, &height, 0, SOIL_LOAD_RGB);
	if(0 == texNames[1])
	{
		printf("SOIL loading error: '%s' while trying to load file %s\n", SOIL_last_result(), model1TexPath);
        exit(-1);
	}
	SOIL_free_image_data(model1Image);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, model1Image);
    model1 -> texture = texNames[1];
    
    
    
    // Texture2 - Model2's Texture
    glBindTexture(GL_TEXTURE_2D, texNames[2]);
    model2Image = SOIL_load_image(model2TexPath, &width, &height, 0, SOIL_LOAD_RGB);
	if(0 == texNames[2])
	{
		printf("SOIL loading error: '%s' while trying to load file %s\n", SOIL_last_result(), model2TexPath);
        exit(-1);
	}
	SOIL_free_image_data(model2Image);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, model2Image);
    model2 -> texture = texNames[2];

    glEnable(GL_TEXTURE_2D);
}

#endif
