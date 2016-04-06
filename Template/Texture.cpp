#include "Texture.h"

Texture::~Texture()
{
}

Texture Texture::createTexture(const std::string& resourcefilepath)
{
	image = res->loadFile<SDL_Surface>(resourcefilepath);

	return texM->makeTexture(image);
}