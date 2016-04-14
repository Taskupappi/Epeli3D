#include "TextureManager.h"

// load image file
void TextureManager::createTexture(const std::string &resourcefilepath)
{
	 image = _res->loadFile<ImageResource>(resourcefilepath);
	
	//width = image->w;
	//height = image->h;
	
	// Call bind method
	//bindTexture(image);
}	