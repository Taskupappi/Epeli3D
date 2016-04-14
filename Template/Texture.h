#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.h"
#include <string.h>
#include "ImageResource.h"

class Texture
{
public:
	Texture(GLuint _texture)
	{
		_texture = NULL;
		
	}
	~Texture(){};
	GLuint bindTexture();
	void unbindTexture();


private:

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}

	//TODO: oma mappi textuureille, joku systeemi hakemaan handle samaa filua ladattaessa?
	std::unordered_map<std::string, Texture>textureMap;
	imageData data;
	GLuint _texture;

};

#endif