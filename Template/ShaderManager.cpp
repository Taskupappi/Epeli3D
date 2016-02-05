#include "ShaderManager.h"


ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{

}

bool ShaderManager::initShader(/*insert shader class here*/)
{
	//create a program for GL to attach shaders into
	programID = glCreateProgram();

	//load a vertexShader and check for errors
	//if(SDL_assert(vertexShaderID = loadshader(/*insert shader class here*/)));
	/*{
		std::cout << "error while loading a vertex shader from the resource manager!" << __LINE__<< "  " << __FILE__ << std::endl;
		glDeleteProgram(programID);
		programID = 0;
		return false;
	}*/

	//attach the shader to the GL program
	glAttachShader(programID, vertexShaderID);

	//Load a fragment shader adn check for errors
	//if (SDL_assert(vertexShaderID = loadShader(/*insert shader class here*/)))
	/*{
	std::cout << "error while loading a fragment shader from the resource manager!" << __LINE__ << "   " << __FILE__ << std::endl;
	glDeleteProgram(programID);
	programID = 0;
	return false;
	}*/

	//attach the fragment shader to the GL program
	glAttachShader(programID, fragmentShaderID);

	//link the GL program
	glLinkProgram(programID);
	
	//check for errors
	GLint LinkSuccess = GL_TRUE;
	glGetProgramiv(programID, GL_LINK_STATUS, &LinkSuccess);

	if (!LinkSuccess)
	{
		std::cout << "error while linking GL program" << programID << " in a file " << __FILE__ << std::endl;
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(programID);
		programID = NULL;
		return false;
	}

	//delete unnecessary shader references after succesful linking
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return true;
}

void ShaderManager::uninit()
{
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
	programID = NULL;
}

void ShaderManager::useShader(/*insert shader here*/)
{
	//glUseProgram(/*insert shader here*/);
}

GLuint ShaderManager::GetShaderProgram()
{
	return programID;
}

//Shader* ShaderManager::loadshader()
//{
//
//}