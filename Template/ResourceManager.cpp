#include "ResourceManager.h"
#include <fstream>


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}
void ResourceManager::loadResource(const std::string fileName)
{
	// find "." in string
	std::string extension = "";
	size_t pos = fileName.find_last_of(".");

	// check if position is valid
	if (pos != std::string::npos)
		extension = fileName.substr(pos + 1);
	else
		printf_s("Could not determine file extension\n");

	//compare to image extensions
	if (extension == "png" | extension == "jpeg" | extension == "gif" | extension == "webp")
		loadImage(fileName);
	
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

void ResourceManager::load3DModel(const std::string fileName)
{
	//Jussi jatkaa tätä
}

void ResourceManager::loadShader(const std::string fileName)
{
	GLuint ShaderID = NULL;
	std::string ShaderString;
	std::ifstream SourceFile((shaderFilePath + fileName).c_str());

	if (SourceFile)
	{
		ShaderString.assign((std::istreambuf_iterator< char >(SourceFile)), std::istreambuf_iterator<char>());
	}
	else
	{
		std::cout << "unable to open source file" << std::endl;
	}
}

void ResourceManager::loadFont(const std::string fileName)
{

}