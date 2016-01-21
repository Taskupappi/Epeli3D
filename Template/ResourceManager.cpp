#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadImage(const std::string fileName)
{
	image = IMG_Load((filePath + fileName).c_str());
	if (!image)
	{
		printf_s("IMG_Load: %s\n", IMG_GetError());
		//handle error
	}
}