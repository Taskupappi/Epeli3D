#include "Texture.h"
#include "ImageResource.h"

// Unbind texture
void Texture::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Bind texture
GLuint Texture::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
		_image->getWidth(),
		_image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		_image->getPixelData());

	setTextureSize(_image->getWidth(), _image->getHeight());

	return _texture;
}

void Texture::setTextureSize(int width, int height)
{
	_texSize.x = width;
	_texSize.y = height;
}

glm::vec2 Texture::getTextureSize()
{
	return _texSize;
}