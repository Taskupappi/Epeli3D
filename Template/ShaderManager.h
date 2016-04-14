#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "Shader.h"

#include <SDL\SDL_assert.h>
#include <map>

//#include "ResourceBase.h"

namespace core
{
	class Engine;
}

//namespace graphics
//{
	class ShaderManager
	{
		friend class core::Engine;

	public:

		//creates and initializes a shader
		void createShader(std::string vertexFilepath, std::string fragmentFilepath, std::string shaderName);
		//uninit shaders
		void uninitShaders(void);

		//set the active shader
		void setActiveShader(std::string shaderName);
		//get the active shader
		Shader* getActiveShader();
		//use the active shader
		void useActiveShader();

		ShaderManager();
		~ShaderManager();

	protected:
	

	private:
		std::map<std::string, Shader*> Shaders;
		Shader* activeShader;
		//Resources *resMngr;
	};
//}
#endif