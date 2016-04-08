//#ifndef SHADERMANAGER_H
//#define SHADERMANAGER_H
//
////TO DO:
////add shader class to the manager
////
//
//#include "Shader.h"
////#include <glm\glm.hpp>
//#include <GL\glew.h>
//#include <SDL\SDL_assert.h>
////#include <iostream>
//#include <map>
//#include <algorithm>
//#include <iostream>
//#include <sstream>
////#include <
//
//#include "ResourceBase.h"
//namespace core
//{
//	class Engine;
//}
//
//
//namespace graphics
//{
//	class ShaderManager
//	{
//		friend class core::Engine;
//	public:
//
//		//create shader
//		void createShader(std::string vertexFilepath, std::string fragmentFilepath);
//
//		//init shaders
//		bool initShader(std::string filepath);
//
//		//uninit shaders
//		void uninitShaders(void);
//
//		//Load shader from resource manager
//		void loadshader(/*insert shader class here*/);
//
//		//Bind shader to the program
//		void bind();
//
//		//set the active shaders
//		//Shader &SetActive();
//		//get shader
//		//GLuint GetShader();
//
//		std::map<std::string, Shader*> Shaders;
//	protected:
//		ShaderManager();
//		~ShaderManager();
//
//	private:
//
//		GLuint programID, matrixID, vertexShaderID, fragmentShaderID;
//		Resources *resMngr;
//	};
//
//
//}
//
//#endif