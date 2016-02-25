#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.h"
#include "ResourceBase.h"
#include <string.h>

class Texture
	: public ResourceBase
{
public:
	Texture(const std::string &resourcefilepath, SDL_Surface* image) : ResourceBase(resourcefilepath, image)
	{
		image = IMG_Load((resourcefilepath).c_str());
		this->image = image;
		// ???? mahtaakohan ees tehh‰ mith‰‰n ????
	}
	//Texture(SDL_Surface*){};
	~Texture(){};

	//Texture* loadFile(const std::string &resourcefilepath)
	//{

	//		/*if (!texturesInit)
	//		{
	//		textures.initResourceManager("TextureDataBase");
	//		TextureMap.initMapper("TextureMap", &textures, true);
	//		}*/
	//		loadedResource = new Texture("Image", (IMG_Load((resourcefilepath).c_str())));
	//		return loadedResource;
	//
	//}

private:
	//Texture(const Texture &texture) : ResourceBase(texture){ }

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}

	Texture* loadedResource;
	SDL_Surface* image = 0;
};

#endif