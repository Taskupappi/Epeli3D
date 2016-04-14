#include "ShaderManager.h"

graphics::ShaderManager::ShaderManager()
{
	
}

graphics::ShaderManager::~ShaderManager()
{

}

Shader* graphics::ShaderManager::createShader(std::string vertexFilepath, std::string fragmentFilepath, std::string shaderName)
{
	Shader *shader = new Shader(vertexFilepath, fragmentFilepath);
	shader->init();

	Shaders[shaderName] = shader;

	return shader;
}

void graphics::ShaderManager::uninitShaders()
{
	std::map<std::string, Shader*>::iterator ShadersIter;
	for (ShadersIter = Shaders.begin(); ShadersIter != Shaders.end(); ShadersIter++)
	{
		delete ShadersIter->second;
		Shaders.erase(ShadersIter);
	}
}

void graphics::ShaderManager::setActive(std::string shaderName)
{
	Shaders.find(shaderName)->second->use();
}