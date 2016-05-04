#include "TextureManager.h"
#include "Texture.h"

// load image file and create texture
Texture* TextureManager::createTexture(const std::string &resourcefilepath)
{
	_image = _res->loadFile<ImageResource>(resourcefilepath);

	Texture* texture = new Texture(0);
	texture->bindTexture(_image);

	Texture* texture = new Texture(0);
	texture->bindTexture(_image);

	return texture;
}