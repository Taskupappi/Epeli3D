#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}
void ResourceManager::loadResource(const std::string fileName)
{
	// find . in string
	// compare to other extensions
	std::string extension = "";
	size_t pos = fileName.find_last_of(".");
	// check if position is valid
	if (pos != std::string::npos)
		extension = fileName.substr(pos + 1);
	else
		printf_s("Could not determine file extension\n");
	////////////////////////////
	//compare extensions

	/////////////////////////
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