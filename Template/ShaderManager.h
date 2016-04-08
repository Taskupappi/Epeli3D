#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

//TO DO:
//add shader class to the manager
//

#include "Shader.h"
//#include <glm\glm.hpp>
#include <GL\glew.h>
#include <SDL\SDL_assert.h>
//#include <iostream>
#include <map>
//#include <

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	//init shaders
	bool initShader(std::string filename);

	//uninit shaders
	void uninitShaders(void);

	//Load shader from resource manager
	void loadshader(/*insert shader class here*/);

	//Bind shader to the program
	void bind();

	//set the active shaders
	//Shader &SetActive();
	//get shader
	/*GLuint GetShader();

	std::map<std::string, Shader*> Shaders;*/

private:

	GLuint programID, matrixID, vertexShaderID, fragmentShaderID;


};


#endif