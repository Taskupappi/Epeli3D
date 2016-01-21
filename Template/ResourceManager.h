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
	const std::string filePath = "../data/Resource/";
	const std::string shaderFilePath = "../data/Shaders/";
	const std::string fileName;
	bool isImage = false;
};

#endif