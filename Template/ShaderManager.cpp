#include "ShaderManager.h"
using namespace graphics;

ShaderManager::ShaderManager() :activeShader(nullptr)
{
	
}

ShaderManager::~ShaderManager()
{

}

Shader * ShaderManager::createShader(std::string vertexFilepath, std::string fragmentFilepath, std::string shaderName)
{
	Shader *shader = new Shader(vertexFilepath, fragmentFilepath, shaderName);
	shader->init();

	Shaders[shaderName] = shader;
	return shader;
}

void ShaderManager::uninitShaders()
{
	std::map<std::string, Shader*>::iterator ShadersIter;
	for (ShadersIter = Shaders.begin(); ShadersIter != Shaders.end(); ShadersIter++)
	{
		delete ShadersIter->second;
		Shaders.erase(ShadersIter);
	}
}

void ShaderManager::setActiveShader(std::string shaderName)
{
	activeShader = Shaders.find(shaderName)->second;
	activeShader->use();
}

void  ShaderManager::useActiveShader()
{
	activeShader->use();
}

Shader* ShaderManager::getActiveShader()
{
	return activeShader;
}