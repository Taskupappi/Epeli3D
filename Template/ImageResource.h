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

	// TODO: FIX GETTERS
	//void setWidth(int width){ _width = width; }
	//void setHeight(int height){ _height = height; }
	//void setPixelData(void* data){ _pixelData = data; }

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
	//int _width = 0;
	//int _height = 0;
	//void* _pixelData;
};

#endif