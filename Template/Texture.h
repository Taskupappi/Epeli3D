#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.h"
#include "ResourceBase.h"
#include <string.h>

class Texture
	: public ResourceBase
{
public:
	Texture(const std::string &resourcefilepath, SDL_Surface* image) : ResourceBase(resourcefilepath, image)
	{
	}
	~Texture(){};

private:

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}

	SDL_Surface* image = 0;
};

#endif