#ifndef ImageResource_H
#define ImageResource_H

#include "Core.h"
#include "ResourceBase.h"
#include <string.h>

class ImageResource
	: public ResourceBase
{
public:
	ImageResource(SDL_Surface* image) : ResourceBase(resourcefilepath, nullptr)
	{
		_image = image;

	}
	~ImageResource(){};

	SDL_Surface *_image;

private:

	ImageResource &operator=(ImageResource &image)
	{
		if (this == &image)
			return *this;
	}
};

#endif