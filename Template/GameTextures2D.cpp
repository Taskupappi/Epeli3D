#include "GameTexture2D.h"

GameTexture2D::GameTexture2D()
	:width(0), height(0), internalFormat(GL_RGB), ImageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
	glGenTextures(1, &this->id);
}

void GameTexture2D::generate(GLuint width, GLuint height, unsigned char* data)
{
	this->width = width;
	this->height = height;
	//create texture
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->ImageFormat, GL_UNSIGNED_BYTE, data);
	//set texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
	//unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameTexture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}