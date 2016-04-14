#include "Texture.h"

// Bind texture and insert it to a map
GLuint Texture::bindTexture()
{
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	//SDL_FreeSurface(&image);
	textureMap.insert(std::pair<std::string, Texture>(data.filePath, _texture));
	return _texture;
}

// Unbind texture
void Texture::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}