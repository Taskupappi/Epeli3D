#ifndef TEXTURE_H
#define TEXTURE_H

#include <string.h>
#include "TextureManager.h"

class ImageResource;

class Texture
{
public:
	friend class TextureManager;

	void unbindTexture();
	GLuint bindTexture(ImageResource* image);
	void setTextureSize(int width, int height);
	glm::vec2 getTextureSize();
	// void deleteTexture();
private:

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}

	GLuint _texture;
	ImageResource *_image;
	glm::vec2 _texSize;

protected:
	Texture(GLuint)
	{
		_texture = NULL;
		_texSize.x = 0;
		_texSize.y = 0;
	}
	~Texture(){};

};

#endif