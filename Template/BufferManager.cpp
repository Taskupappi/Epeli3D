#include "BufferManager.h"

BufferManager::BufferManager()
{
	initBuffers();

	initShaders();
}

BufferManager::~BufferManager()
{
	if (vertexbufId != 0)
	{
		glDeleteBuffers(1, &vertexbufId);
	}

	if (indexbufID != 0)
	{
		glDeleteBuffers(1, &indexbufID);
	}	
}

void BufferManager::bindBuffer()
{
	if (vertexBuffer.size() != 0)
	{
	
	}
}

void BufferManager::addVertexData(GLfloat *data, GLsizei size)
{	
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufId);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat),
		data, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//tex Coord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	vertexBuffer.push_back(vertexbufId);
	
}

void BufferManager::addIndexData(GLfloat *data, GLsizei *size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLfloat),
		size, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	indexBuffer.push_back(indexbufID);
}

void BufferManager::drawBuffer(std::vector<GLuint> buffer)
{	
	
	//Clear the backbuffer and the depth-buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);

	
	for (int i = 0; i < vertexBuffer.size() - 1; i++)
	{
		glBindVertexArray(vertexBuffer[i]);
		glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));	
	}

	glBindVertexArray(0);

}

void BufferManager::initBuffers()
{
	vertexbufId = 0;
	glGenBuffers(1, &vertexbufId);

	indexbufID = 1;
	glGenBuffers(1, &indexbufID);
}

void BufferManager::initShaders()
{
	// Shaders
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";


	//vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//End of Shader init and linking
}