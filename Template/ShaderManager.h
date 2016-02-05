#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

//TO DO:
//add shader class to the manager
//


#include <glm\glm.hpp>
#include <GL\glew.h>
#include <SDL\SDL_assert.h>
#include <iostream>

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	//init shaders
	bool initShader(/*insert shader class here*/);
	//uninit shaders
	void uninit(void);
	//Load shader from resource manager
	void loadshader(/*insert shader class here*/);
	//Bind shader to the program
	void bind();
	//use shader the given shaders in the application
	void useShader(/*insert shader class here*/);
	//set the active shaders
	//Shader &SetActive();
	//get shader
	GLuint GetShaderProgram();

private:

	GLuint programID, matrixID, vertexShaderID, fragmentShaderID;


};


#endif