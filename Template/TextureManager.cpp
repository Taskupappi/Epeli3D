#include "TextureManager.h"



// load image file
ImageResource* TextureManager::createTexture(const std::string &resourcefilepath)
{
	 _image = _res->loadFile<ImageResource>(resourcefilepath);

	 return _image;
}