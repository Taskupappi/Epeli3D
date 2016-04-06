#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.h"
#include "ResourceBase.h"
#include "TextureManager.h"
#include <string.h>

class Resources;

class Texture
	: public ResourceBase
{
public:
	Texture(GLuint _texture) : ResourceBase(resourcefilepath, nullptr)
	{
		_texture = NULL;
		res = new Resources("TextureResource", 0);
	}
	~Texture(){};

	Texture createTexture(const std::string& resourcefilepath);

	GLuint _texture;

private:

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}

	Resources *res;
	TextureManager *texM;
	SDL_Surface* image;
};

#endif