#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Texture.h"
#include "Resources.h"

class TextureManager
	: public Texture
{
public:
	TextureManager() : Texture(_texture)
	{
		texture = _texture;
	}
	~TextureManager();

	Texture makeTexture(SDL_Surface* image);

private:

	GLuint texture;
};

#endif