#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "Core.h"
#include <iostream>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void loadResource(const std::string fileName);
	void loadImage(const std::string fileName);
	void load3DModel(const std::string fileName);
	void loadShader(const std::string fileName);
	void loadFont(const std::string fileName);
	void loadSound(const std::string fileName);

private:
	SDL_Surface *image;
	const std::string imageFilePath = "../data/Resource/Images/";
	const std::string audioFilePath = "../data/Resource/Audio/";
	const std::string shaderFilePath = "../data/Shaders/";
	const std::string fontFilePath = "../data/Fonts/";
	const std::string fileName;
};

#endif