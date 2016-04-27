#ifndef TEXTURE_H
#define TEXTURE_H

#include <string.h>
#include "TextureManager.h"

class ImageResource;

class Texture
{
public:
	friend class TextureManager;

	Texture(){};
	Texture(TextureManager* texM)
	{
		_texM = texM;
		_texture = NULL;
	}
	~Texture(){};

	GLuint createTexture(const std::string& resourcefilepath);
	void unbindTexture();

private:

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}

	GLuint _texture;
	ImageResource *_image;
	TextureManager* _texM;
};

#endif