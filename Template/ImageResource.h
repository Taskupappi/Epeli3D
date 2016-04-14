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
		_width = 0;
		_height = 0;
		_pixelData = 0;
		//setWidth(image->w);

		//setHeight(image->h);

		//setPixelData(image->pixels);

		//filePath = resourcefilepath;
	}
	~ImageResource(){};

	// FIX GETTERS
	void setWidth(int width){ _width = width; }
	void setHeight(int height){ _height = height; }
	void setPixelData(void* data){ _pixelData = data; }

	int getWidth(){	return _width; }
	int getHeight(){ return _height; }
	void* getPixelData(){ return _pixelData; }

private:

	ImageResource &operator=(ImageResource &image)
	{
		if (this == &image)
			return *this;
	}
	SDL_Surface *_image;
	int _width;
	int _height;
	void* _pixelData;
	std::string _filePath;
};

#endif