#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "Core.h"
#include <iostream>
#include <typeinfo>
#include <vector>
#include <fstream>
class Image
{
public:
	Image(){};
	~Image(){};

private:
	std::vector<unsigned char> imageData;
};
class ResourceManager
{
public:
	ResourceManager(){};
	~ResourceManager(){};
	template< typename T>
	T* loadResourceT(const std::string fileName)
	{
		{
			switch (typeid(T))
			{
			case typeid(image) :
				image * img = loadImage(fileName);
				return img;
				break;
				// case typeid(audio).name():
			default:
				break;
			}
		}
	}
	void loadResource(const std::string fileName);
	void loadImage(const std::string fileName);
	void load3DModel(const std::string fileName);
	void loadShader(const std::string fileName);
	void loadFont(const std::string fileName);
	void loadSound(const std::string fileName);

private:
	SDL_Surface *image;
	Mix_Music *audio;
	const std::string imageFilePath = "../data/Resource/Images/";
	const std::string audioFilePath = "../data/Resource/Audio/";
	const std::string modelFilePath = "../data/Resource/Models/";
	const std::string shaderFilePath = "../data/Shaders/";
	const std::string fontFilePath = "../data/Fonts/";
	const std::string fileName;
};

#endif