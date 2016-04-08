//#include "ShaderManager.h"
//
//graphics::ShaderManager::ShaderManager() 
//{
//;
//}
//
//graphics::ShaderManager::~ShaderManager()
//{
//
//}
//
//void graphics::ShaderManager::createShader(std::string vertexFilepath, std::string fragmentFilepath)
//{
//	Shader *shader = new Shader();
//
//	//1. retrive vertex/ fragment source code from the resource manager
//	std::string vertexCode;
//	std::string fragmentCode;
//	
//	//vertexCode = resMngr->loadFile(vertexFilepath);		//waiting for proper resource implementation
//	//fragmentCode = resMngr->loadFile(fragmentFilepath);	// waiting for proper resource implementation
//	
//	const GLchar *vertexShaderCode = vertexCode.c_str();
//	const GLchar *fragmentShaderCode = 
//
//	//shader->init()
//}
//
//bool graphics::ShaderManager::initShader(std::string filepath)
//{
//
//
//	std::string filename = filepath;
//	std::reverse(filename.begin(), filename.end());
//	filename = filename.substr(0, filename.find("/"));
//	std::reverse(filename.begin(), filename.end());
//	filename = filename.substr(0, filename.find("."));
//	
//	Shader *shader = new Shader();
//
//	//shader = 
//
//	Shaders.insert(std::make_pair(filename, shader));
//	return true;
//
//
//}
//
//void graphics::ShaderManager::uninitShaders()
//{
//	/*glDeleteShader(vertexShaderID);
//	glDeleteShader(fragmentShaderID);
//	glDeleteProgram(programID);
//	programID = NULL;*/
//}
//
////GLuint ShaderManager::GetShader()
////{
////	return 1; // programID;
////}
//
////Shader* ShaderManager::loadshader()
////{
////
////}