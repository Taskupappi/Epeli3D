#ifndef GAMESHADER_H
#define GAMESHADER_H

#include <GL\glew.h>
#include <glm\glm.hpp>

#include <iostream>
#include <string>
#include <glm\gtc\type_ptr.hpp>


class GameShader
{
public:
	GameShader(){};
	~GameShader(){};
	
	//sets the current shader as active
	GameShader &use();

	//Compiles the shader from given source code
	//Note: geometry source code is optional
	void compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr); 
	
	//utility stuff
	void setFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void setInt(const GLchar *name, GLfloat value, GLboolean usehader = false);
	void setVec2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void setVec2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void setVec3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void setVec3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void setVec4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void setVec4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

	GLuint id;

private:
	//checks for errors
	void checkCompileErrors(GLuint object, std::string type);
};

#endif