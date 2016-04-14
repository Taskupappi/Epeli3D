#include "TextureManager.h"

// load image file
void TextureManager::createTexture(const std::string &resourcefilepath)
{
	 image = _res->loadFile<ImageResource>(resourcefilepath);
}

//GLuint TextureManager::getWidth(ImageResource &image)
//{
//
//}
//
//GLuint TextureManager::getHeight(ImageResource &image)
//{
//
//}