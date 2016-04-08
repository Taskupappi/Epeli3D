#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Texture.h"
#include "Resources.h"
#include "ResourceBase.h"

class TextureManager
	: public ResourceBase
{
	friend class Texture;
public:
	TextureManager(Resources *res) : ResourceBase(resourcefilepath, nullptr)
	{
		_res = res;
		texture = 0;
		width = 0;
		height = 0;
	}
	~TextureManager(){};

	GLuint createTexture(const std::string& resourcefilepath);
	GLuint bindTexture(SDL_Surface& image);
	void unbindTexture();
	int getWidth();
	int getHeight();

private:
	//TODO: oma mappi textuureille, joku systeemi hakemaan handle samaa filua ladattaessa?
	std::unordered_map<std::string, Texture>textureMap;
	Resources *_res;
	GLuint texture;
	SDL_Surface* image;
	int width;
	int height;
};

#endif