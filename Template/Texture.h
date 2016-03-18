#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.h"
#include "ResourceBase.h"
#include <string.h>

class Texture
	: public ResourceBase
{
public:
	Texture(const std::string &resourcefilepath, GLuint image) : ResourceBase(resourcefilepath, nullptr)
	{
		_image = image;
	}
	~Texture(){};

private:

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}

	GLuint _image;
};

#endif