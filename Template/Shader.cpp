#include "Shader.h"

Shader::Shader(const std::string vertexFilepath, const std::string fragmentFilepath)
	:vertexShaderPath(vertexFilepath), fragmentShaderPath(fragmentFilepath)
{
}

Shader::~Shader()
{
}


void Shader::use()
{
	glUseProgram(this->programID);
}

GLuint Shader::getShaderProgram()
{
	return programID;
}

GLint Shader::getUniformLocation(std::string uniformLocName)
{
	const char *uLN = uniformLocName.c_str();
	GLint uniformLocation = glGetUniformLocation(this->getShaderProgram(), uLN);
	return uniformLocation;
}

bool Shader::init()
{

	//can be removed from here once it's made sure it's initialized before creating shaders
	glewInit();

	//create program
	programID = glCreateProgram();


	//Load vertex Shader and attach it to a program
	vertexShaderID = loadShaderFromFile(vertexShaderPath, GL_VERTEX_SHADER);

	//check for errors
	if (vertexShaderID == NULL)
	{
		std::cout << "error while loading VertexShader" << vertexShaderID << "\n on line " << __LINE__ << std::endl;
		glDeleteProgram(programID);
		programID = 0;
		return false;
	}

	//link vertex shader to the program
	glAttachShader(programID, vertexShaderID);
	////


	//load vertex Shader
	fragmentShaderID = loadShaderFromFile(fragmentShaderPath, GL_FRAGMENT_SHADER);

	//check for errors
	if (fragmentShaderID == NULL)
	{
		std::cout << "error while loading FragmentShader" << fragmentShaderID << "\n on line " << __LINE__ << "\n in a file:" << __FILE__ << std::endl;
		glDeleteShader(fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteProgram(programID);
		programID = NULL;
		return false;
	}

	//link fragment shader to the program
	glAttachShader(programID, fragmentShaderID);
	////


	//link the program
	glLinkProgram(programID);

	//check for linking errors
	GLint LinkSuccess = GL_TRUE;
	glGetProgramiv(programID, GL_LINK_STATUS, &LinkSuccess);

	if (LinkSuccess != GL_TRUE)
	{
		std::cout << "error while linking program: " << programID << std::endl;
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(programID);
		programID = NULL;
		return false;
	}

	//remove unnecessary references
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	return true;
}

GLuint Shader::loadShaderFromFile(const std::string filepath, GLenum ShaderType)
{
	GLuint ShaderID = NULL;
	std::string ShaderString;
	std::ifstream SourceFile(filepath.c_str());

	if (SourceFile)
	{
		ShaderString.assign((std::istreambuf_iterator< char >(SourceFile)), std::istreambuf_iterator<char>());
	}
	else
	{
		std::cout << "unable to open source file: " << filepath << std::endl;
	}

	//set and ID for the Shader
	ShaderID = glCreateShader(ShaderType);

	//shader's source
	const GLchar* ShaderSource = ShaderString.c_str();
	glShaderSource(ShaderID, 1, (const GLchar**)&ShaderSource, NULL);

	//compile shader
	glCompileShader(ShaderID);

	//check for errors
	GLint ShaderCompiled = GL_FALSE;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &ShaderCompiled);

	if (ShaderCompiled != GL_TRUE)
	{
		std::cout << "Unable to compile shader \n" << ShaderID << "\n Source: \n" << ShaderSource << std::endl;
		glDeleteShader(ShaderID);
		ShaderID = NULL;
	}

	return ShaderID;
}