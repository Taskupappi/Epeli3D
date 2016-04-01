#ifndef GRM_H
#define GRM_H

#include <SOIL\SOIL.h>

#include <map>
#include <string>

#include <iostream>
#include <sstream>
#include <fstream>

#include <GL\glew.h>

#include "GameTexture2D.h"
#include "GameShader.h"

class GameResourceManager
{
public:
	//loads vertex, fragment and geometry shaders
	static GameShader loadShader(const GLchar *vShaderFilePath, const GLchar *fShaderFilePath, const GLchar *gShaderFilePath, std::string name);
	//retrieve a stored shader
	static GameShader getShader(std::string name);


	static GameTexture2D loadTexture(const GLchar* file, GLboolean aplha, std::string name); 
	static GameTexture2D getTexture(std::string name);

	//Resource storage
	static std::map<std::string, GameShader> shaders;
	static std::map<std::string, GameTexture2D> textures;

	static void clear();
private:
	GameResourceManager(){};
	static GameShader loadShaderFromFile(const GLchar *vShaderFile,
	const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	static GameTexture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif