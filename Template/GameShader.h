#ifndef GAMESHADER_H
#define GAMESHADER_H

#include <GL\glew.h>
#include <iostream>
#include <glm\glm.hpp>

#include <fstream>
#include <istream>
#include <sstream>

class GameShader
{
public:
	GameShader();
	~GameShader();

	//initialisoi shaderit, pistä ohjelman alkuun
	bool init(std::string vertexShaderName, std::string fragmentShaderName);
	void uninit(void);
	//void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	GLuint loadShaderFromFile(const std::string filepath, GLenum ShaderType);
	void use();
	GameShader &setActive();
	GLuint getShaderProgram();

	GLint getUniformLocation(std::string uniformLocName, glm::vec3 value);

	//utility stuff
	void setUniform3f(std::string uniformLocation, glm::vec3 values);

	void setFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void setInteger(const GLchar *name, GLfloat value, GLboolean usehader = false);
	void setVec2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void setVec2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void setVec3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void setVec3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void setVec4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void setVec4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

private:
	GLuint programID;
	GLuint matrixID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID, fragmentShaderID2;
};

#endif