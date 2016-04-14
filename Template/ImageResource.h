#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

#include "Core.h"
#include "ResourceBase.h"

struct imageData
{
	GLuint width;
	GLuint height;
	void* pixels;
	std::string filePath;
};

class ImageResource
	: public ResourceBase
{
public:
	ImageResource(SDL_Surface* image) : ResourceBase(resourcefilepath, nullptr)
	{
		_image = image;
		data.width = _image->w;
		data.height = _image->h;
		data.pixels = _image->pixels;
		data.filePath = resourcefilepath;
	}
	~ImageResource(){};

private:

	ImageResource &operator=(ImageResource &image)
	{
		if (this == &image)
			return *this;
	}
	SDL_Surface *_image;
	imageData data;
};

#endif