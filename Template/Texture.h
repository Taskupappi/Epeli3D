#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.h"
#include <string.h>
#include "TextureManager.h"
//#include "ImageResource.h"
class ImageResource;

class Texture
{
public:
	friend class TextureManager;
	Texture(TextureManager* texM)
	{
		_texM = texM;
		_texture = NULL;
	}
	~Texture(){};
	GLuint createTexture(const std::string& resourcefilepath);
	//GLuint bindTexture(ImageResource *img);
	void unbindTexture();


private:

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}

	//TODO: oma mappi textuureille, joku systeemi hakemaan handle samaa filua ladattaessa?
	std::unordered_map<std::string, GLuint>textureMap;
	GLuint _texture;
	ImageResource *_image;
	Resources *_res;
	TextureManager* _texM;

};

#endif