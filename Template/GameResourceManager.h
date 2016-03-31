#ifndef GRM_H
#define GRM_H

#include "GameShader.h"
#include <map>


class GameResourceManager
{
public:
	//loads vertex, fragment and geometry shaders
	static GameShader loadShader(const GLchar *vShaderFilepath, const GLchar *fShaderFilepath, const GLchar *gShaderFile, std::string name);
	//retrieve a stored shader
	static GameShader getShader(std::string name);


	//static texture2D loadTexture(const GLchar* file, GLboolean aplha, std::string name); 
	//static texture2D getTexture(std::string name);

	//Resource storage
	static std::map<std::string, GameShader> Shaders;
	//static std::map<std::string, Texture2D> textures;

	static void clear();
private:
	GameResourceManager(){};
	static GameShader loadFromFile(const GLchar *vShaderFile,
		const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);

	//static texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif