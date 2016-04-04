#ifndef GT2D_H
#define GT2D_H

#include <GL\glew.h>

class 
	GameTexture2D
{
public:
	
	GameTexture2D();
	
	void generate(GLuint width, GLuint height, unsigned char* data);
	void bind() const;
	
	//holds the ID of texture object
	GLuint id;
	//texture image dimensions
	GLuint width, height;
	//texture format
	GLuint internalFormat; //format of texture object
	GLuint ImageFormat; //format of loaded image

	//Texture config
	GLuint wrapS; //wrapping mode on S axis
	GLuint wrapT; //wrapping mode on T axis
	GLuint filterMin; //filtering mode if texture pixels < screen pixels
	GLuint filterMax; //filtering mode if texture pixels > screen pixels
private:
};

#endif