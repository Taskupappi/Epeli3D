#include "TextureManager.h"



// load image file
ImageResource* TextureManager::loadImage(const std::string &resourcefilepath)
{
	_image = _res->loadFile<ImageResource>(resourcefilepath);

	return _image;
}