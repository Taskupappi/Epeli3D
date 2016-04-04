#include "GameResourceManager.h"

//instantiate static variables
std::map<std::string, GameShader> GameResourceManager::shaders;
std::map<std::string, GameTexture2D> GameResourceManager::textures;


GameShader GameResourceManager::loadShader(const GLchar *vShaderFilePath, const GLchar *fShaderFilePath, const GLchar *gShaderFilePath, std::string name)
{
	shaders[name] = loadShaderFromFile(vShaderFilePath, fShaderFilePath, gShaderFilePath);
	return shaders[name];
}

GameShader GameResourceManager::getShader(std::string name)
{
	return shaders[name];
}

GameTexture2D GameResourceManager::loadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	textures[name] = loadTextureFromFile(file, alpha);
	return textures[name];
}

GameTexture2D GameResourceManager::getTexture(std::string name)
{
	return textures[name];
}

void GameResourceManager::clear()
{
	for (auto iter : shaders)
		glDeleteProgram(iter.second.id);

	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.id);
}

GameShader GameResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{

	// 1. Retrieve the vertex / fragment source code from filepath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try
	{
		//open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		//ready file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		//close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		//conver stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		//if geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}

	}
	catch (std::exception error)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	//2. create shader object from source code
	GameShader shader;
	shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

	return shader;
}

GameTexture2D GameResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	//create texture object
	GameTexture2D texture;
	if (alpha)
	{
		texture.internalFormat = GL_RGBA;
		texture.ImageFormat = GL_RGBA;
	}
	//load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.ImageFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

	//generate texture
	texture.generate(width, height, image);
	//free image data
	SOIL_free_image_data(image);
	return texture;
}