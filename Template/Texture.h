#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.h"
#include <string.h>

class Texture
{
public:
	Texture(GLuint _texture)
	{
		_texture = NULL;
		
	}
	~Texture(){};

	GLuint _texture;

private:

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}
};

#endif