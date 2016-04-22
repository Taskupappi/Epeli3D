#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "ImageResource.h"
#include "Resources.h"
#include "ResourceBase.h"

class TextureManager
	: public ResourceBase
{
	friend class Resources;
public:
	TextureManager(Resources *res) : ResourceBase(resourcefilepath, nullptr)
	{
		_res = res;
	}
	~TextureManager(){};

	ImageResource* loadImage(const std::string& resourcefilepath);

private:
	Resources *_res;
	ImageResource* _image;
};

#endif