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
		width = 0;
		height = 0;
	}
	~TextureManager(){};

	void createTexture(const std::string& resourcefilepath);
	GLuint bindTexture(ImageResource& image);
	void unbindTexture();
	//GLuint getWidth(ImageResource& image);
	//GLuint getHeight(ImageResource& image);

private:
	Resources *_res;
	ImageResource* image;
	int width;
	int height;
};

#endif