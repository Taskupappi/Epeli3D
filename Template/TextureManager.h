#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Texture.h"
#include "Resources.h"

class Resources;

class TextureManager
	: public Texture
{
public:
	TextureManager() : Texture(_texture)
	{
		texture = _texture;
		res = new Resources("TextureResource", 0);
	}
	~TextureManager();

	Texture createTexture(const std::string& resourcefilepath);

private:

	//GLuint texture;
	Resources *res;
	SDL_Surface* image;
	GLuint texture;
};

#endif