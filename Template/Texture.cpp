#include "Texture.h"
#include "ImageResource.h"


GLuint Texture::createTexture(const std::string& resourcefilepath)
{
	_image = _texM->loadImage(resourcefilepath);

	glGenTextures(1, &_texture);
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
	//glGenerateMipmap(GL_TEXTURE_2D);

	return _texture;
}

// Unbind texture
void Texture::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}