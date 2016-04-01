#include "GameShader.h"

GameShader &GameShader::use()
{
	glUseProgram(this->id);
	return *this;
}

void GameShader::compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource)
{
	GLuint sVertex, sFragment, gShader;
	
	//Vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");

	//Fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");

	//if geometry shader source code is give, also compile geometry shader
	if (geometrySource != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}

	//shader program
	this->id = glCreateProgram();
	glAttachShader(this->id, sVertex);
	glAttachShader(this->id, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(this->id, gShader);
	glLinkProgram(this->id);
	checkCompileErrors(this->id, "PROGRAM");

	//delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		glDeleteShader(gShader);
}

void GameShader::setFloat(const GLchar *name, GLfloat value, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform1f(glGetUniformLocation(this->id, name), value);
}
void GameShader::setInt(const GLchar *name, GLfloat value, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform1i(glGetUniformLocation(this->id, name), value);
}
void GameShader::setVec2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform2f(glGetUniformLocation(this->id, name), x, y);
}
void GameShader::setVec2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}
void GameShader::setVec3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}
void GameShader::setVec3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}
void GameShader::setVec4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}
void GameShader::setVec4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}
void GameShader::setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
	if (useShader)
		this->use();
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void GameShader::checkCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
			<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}	
}
