#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <iostream>
#include <glm\glm.hpp>

#include <fstream>
#include <istream>
#include <sstream>

//#include "ResourceMap.h"

//class ResourceMap;

class Shader
{
public:
	Shader(const std::string vertexFilepath, const std::string fragmentFilepath);
	~Shader();

	bool init();
	void uninit(void);

	GLuint loadShaderFromFile(const std::string filepath, GLenum ShaderType);
	void use();
	GLuint getShaderProgram();
	GLint getUniformLocation(std::string uniformLocName);

	//utility stuff -- IS THIS NEEDED?
	//void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	//void SetInteger(const GLchar *name, GLfloat value, GLboolean usehader = false);
	//void SetVec2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	//void SetVec2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	//void SetVec3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	//void SetVec3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	//void SetVec4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	//void SetVec4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	//void SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

private:
	GLuint programID;
	GLuint matrixID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;


	std::string vertexShaderPath;
	std::string fragmentShaderPath;


};

#endif