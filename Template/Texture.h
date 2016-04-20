#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.h"
#include <string.h>
#include "ImageResource.h"
//class ImageResource;

class Texture
{
public:
	Texture(GLuint _texture)
	{
		_texture = NULL;	
	}
	~Texture(){};
	GLuint bindTexture(ImageResource* img);
	void unbindTexture();


private:

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}

	//TODO: oma mappi textuureille, joku systeemi hakemaan handle samaa filua ladattaessa?
	std::unordered_map<std::string, Texture>textureMap;
	GLuint _texture;
	//ImageResource *img;

};

#endif