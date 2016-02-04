#include "TempShader.h"
#include <fstream>

Shader::Shader()
{
}


Shader::~Shader()
{
}

bool Shader::Init()
{
	glewInit();
	//luodaan ohjelma
	ProgramID = glCreateProgram();

	//ladataan vertex Shader
	VertexShaderID = LoadShaderFromFile("../data/shaders/VertexShaderTest.glvs", GL_VERTEX_SHADER);

	//tarkastetaan errorit
	if (VertexShaderID == NULL)
	{
		std::cout << "error while loading VertexShader" << VertexShaderID << "\n on line " << __LINE__ << std::endl;
		glDeleteProgram(ProgramID);
		ProgramID = 0;
		return false;
	}

	//Vertex shaderin kiinnitys ohjelmaan
	glAttachShader(ProgramID, VertexShaderID);

	//ladataan Fragment Shader
	FragmentShaderID = LoadShaderFromFile("../data/shaders/FragmentShaderTest.glfs", GL_FRAGMENT_SHADER);

	//tarkastetaan errorit
	if (FragmentShaderID == NULL)
	{
		std::cout << "error while loading FragmentShader" << FragmentShaderID << "\n on line " << __LINE__ << std::endl;
		glDeleteShader(VertexShaderID);
		glDeleteProgram(ProgramID);
		ProgramID = NULL;
		return false;
	}

	//Fragment Shaderin kiinnitys ohjelmaan
	glAttachShader(ProgramID, FragmentShaderID);

	//ohjelman linkkaus
	glLinkProgram(ProgramID);

	//tarkastetaan errorit
	GLint LinkSuccess = GL_TRUE;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &LinkSuccess);

	if (LinkSuccess != GL_TRUE)
	{
		std::cout << "error while linking program: " << ProgramID << std::endl;
		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
		glDeleteProgram(ProgramID);
		ProgramID = NULL;
		return false;
	}

	//poistetaan turhat shader referenssit, GL säilyttää ne automaattisesti mikäli ne ovat ohjelman käytössä
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	// print out some info about the graphics drivers
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;


	return true;
}

GLuint Shader::LoadShaderFromFile(const std::string filepath, GLenum ShaderType)
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
		std::cout << "unable to open source file" << std::endl;
	}

	//shaderille ID
	ShaderID = glCreateShader(ShaderType);

	//shaderin source
	const GLchar* ShaderSource = ShaderString.c_str();
	glShaderSource(ShaderID, 1, (const GLchar**)&ShaderSource, NULL);

	//shaderin compilaus
	glCompileShader(ShaderID);

	//tarkastusta virheiden varalta
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

void Shader::Use()
{
	glUseProgram(this->ProgramID);
}

GLuint Shader::GetShaderProgram()
{
	return ProgramID;
}

Shader &Shader::SetActive()
{
	glUseProgram(this->ProgramID);
	return *this;
}

void Shader::SetFloat(const GLchar *name, GLfloat value, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform1f(glGetUniformLocation(this->ProgramID, name), value);
}

void Shader::SetInteger(const GLchar *name, GLfloat value, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform1i(glGetUniformLocation(this->ProgramID, name), value);
}

void Shader::SetVec2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform2f(glGetUniformLocation(this->ProgramID, name), x, y);
}

void Shader::SetVec2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform2f(glGetUniformLocation(this->ProgramID, name), value.x, value.y);
}

void Shader::SetVec3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform3f(glGetUniformLocation(this->ProgramID, name), x, y, z);
}

void Shader::SetVec3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform3f(glGetUniformLocation(this->ProgramID, name), value.x, value.y, value.z);
}

void Shader::SetVec4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform4f(glGetUniformLocation(this->ProgramID, name), x, y, z, w);
}

void Shader::SetVec4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform4f(glGetUniformLocation(this->ProgramID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	//glUniformMatrix4fv(glGetUniformLocation(this->ProgramID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
