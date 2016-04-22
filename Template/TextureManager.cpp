#include "TextureManager.h"



// load image file
ImageResource* TextureManager::loadImage(const std::string &resourcefilepath)
{
<<<<<<< HEAD
	 _image = _res->loadFile<ImageResource>(resourcefilepath);
	 
	 return _image;
=======
	ImageResource* _image = _res->loadFile<ImageResource>(resourcefilepath);

	return _image;
>>>>>>> refs/remotes/origin/master
}