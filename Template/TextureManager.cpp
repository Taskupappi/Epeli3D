#include "TextureManager.h"

// load image file, bind it to a texture and insert to a map
GLuint TextureManager::createTexture(const std::string &resourcefilepath)
{
	image = _res->loadFile<SDL_Surface>(resourcefilepath);
	
	width = image->w;
	height = image->h;
	
	// Call bind method
	bindTexture(*image);
}	
// Bind texture
GLuint TextureManager::bindTexture(SDL_Surface &image)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(&image);
	textureMap.insert(std::pair<std::string, Texture>(resourcefilepath, texture));
	return texture;
}

// Unbind texture
void TextureManager::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
// Returns 
int TextureManager::getWidth()
{
	return width;
}

int TextureManager::getHeight()
{
	return height;
}