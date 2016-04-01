#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.h"
#include "ResourceBase.h"
#include <string.h>

class Texture
	: public ResourceBase
{
public:
	Texture(GLuint _texture) : ResourceBase(resourcefilepath, nullptr)
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