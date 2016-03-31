#include "GameShader.h"

GameShader::GameShader()
{

}

GameShader::~GameShader()
{

}

bool GameShader::init(std::string vertexShaderName, std::string fragmentShaderName)
{
	glewInit();

	//1. retrive the vertex / fragment source code from filepath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//ensures ifstrean obhects cab throw exceptions
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		const char *vShader = vertexShaderName.c_str();
		const char *fShader = fragmentShaderName.c_str();

		//open files
		vShaderFile.open(vShader);
		fShaderFile.open(fShader);
		std::stringstream vShaderStream, fShaderStream;
		
		//Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//close file handlers
		vShaderFile.close();
		fShaderFile.close();

		//conver stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();

	// 2. compile Shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	//vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	//print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//shader program
	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertex);
	glAttachShader(this->programID, fragment);
	glLinkProgram(this->programID);

	//print linking errors if any
	glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->programID, 521, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return true;
}

GLuint GameShader::loadShaderFromFile(const std::string filepath, GLenum ShaderType)
{
	GLuint shaderID = NULL;
	std::string shaderString;
	std::ifstream sourceFile(filepath.c_str());

	if (sourceFile)
	{
		shaderString.assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
	}
	else
	{
		std::cout << "unable to open source file" << std::endl;
	}

	//shaderille ID
	shaderID = glCreateShader(ShaderType);

	//shaderin source
	const GLchar* shaderSource = shaderString.c_str();
	glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

	//shaderien compilaus
	glCompileShader(shaderID);

	//tarkastusta virheiden varalta
	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);

	if (shaderCompiled != GL_TRUE)
	{
		std::cout << "Unable to compile shader \n" << shaderID << "\n Source: \n" << shaderSource << std::endl;
		glDeleteShader(shaderID);
		shaderID = NULL;
	}

	return shaderID;
}

GLint GameShader::getUniformLocation(std::string uniformLocName, glm::vec3 value)
{
	const char *c = uniformLocName.c_str();
	GLint uniformLocation = glGetUniformLocation(getShaderProgram(), c);
	glUniform3f(uniformLocation, value.x, value.y, value.z);
}

void GameShader::use()
{
	glUseProgram(this->programID);
}

GLuint GameShader::getShaderProgram()
{
	return programID;
}

GameShader &GameShader::setActive()
{
	glUseProgram(this->programID);
	return *this;
}

void GameShader::setFloat(const GLchar *name, GLfloat value, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform1f(glGetUniformLocation(this->programID, name), value);
}

void GameShader::setInteger(const GLchar *name, GLfloat value, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform1i(glGetUniformLocation(this->programID, name), value);
}

void GameShader::setVec2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform2f(glGetUniformLocation(this->programID, name), x, y);
}

void GameShader::setVec2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform2f(glGetUniformLocation(this->programID, name), value.x, value.y);
}

void GameShader::setVec3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform3f(glGetUniformLocation(this->programID, name), x, y, z);
}

void GameShader::setVec3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform3f(glGetUniformLocation(this->programID, name), value.x, value.y, value.z);
}

void GameShader::setVec4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform4f(glGetUniformLocation(this->programID, name), x, y, z, w);
}

void GameShader::setVec4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform4f(glGetUniformLocation(this->programID, name), value.x, value.y, value.z, value.w);
}

void GameShader::setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
}