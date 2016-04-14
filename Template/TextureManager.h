#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Texture.h"
#include "ImageResource.h"
#include "Resources.h"
#include "ResourceBase.h"

class TextureManager
	: public ResourceBase
{
	friend class Texture;
public:
	TextureManager(Resources *res) : ResourceBase(resourcefilepath, nullptr)
	{
		_res = res;
	}
	~TextureManager(){};

	void createTexture(const std::string& resourcefilepath);

private:
	Resources *_res;
	ImageResource* image;
};

#endif