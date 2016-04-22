#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

#include "Core.h"
#include "ResourceBase.h"


class ImageResource
	: public ResourceBase
{
public:
	ImageResource(SDL_Surface* image) : ResourceBase(resourcefilepath, nullptr)
	{
		_image = image;
	}
	~ImageResource(){};

	int getWidth()
	{
		return _image->w;
	}
	int getHeight()
	{
		return _image->h;
	}
	void* getPixelData()
	{
		return _image->pixels;
	}

private:

	ImageResource &operator=(ImageResource &image)
	{
		if (this == &image)
			return *this;
	}
	SDL_Surface *_image;
};

#endif