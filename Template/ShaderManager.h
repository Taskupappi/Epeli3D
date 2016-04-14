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

namespace graphics
{
	class ShaderManager
	{
		friend class core::Engine;

	public:

		//creates and initializes a shader
		Shader* createShader(std::string vertexFilepath, std::string fragmentFilepath, std::string shaderName);
		//uninit shaders
		void uninitShaders(void);
		//set the active shaders
		void setActive(std::string shaderName);

	protected:
		ShaderManager();
		~ShaderManager();

	private:
		std::map<std::string, Shader*> Shaders;
		//Resources *resMngr;
	};
}
#endif