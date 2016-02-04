#include "BufferManager.h"

BufferManager::BufferManager()
{
	//initShaders();

	initBuffers();
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


void BufferManager::initBuffers()
{
	//vertexbufId = 0;
	//glGenBuffers(1, &vertexbufId);
	//
	//indexbufID = 1;
	//glGenBuffers(1, &indexbufID);

	glGenVertexArrays(1, &this->VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);
	glGenBuffers(1, &ElementBufferObject);

	//glBindVertexArray(this->VertexArrayObject);
	//glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObject);
	//
	//glBufferData(GL_ARRAY_BUFFER, this->vertexBuffer.size()* sizeof(BufferVertex),
	//	&this->vertexBuffer[0], GL_STATIC_DRAW);
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBufferObject);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesBuffer.size() * sizeof(GLuint),
	//	&this->indicesBuffer[0], GL_STATIC_DRAW);
	//
	////Vertex Positions
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BufferVertex),
	//	(GLvoid*)0);
	//
	////Vertex Normals
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BufferVertex),
	//	(GLvoid*)offsetof(BufferVertex, Normal));
	//
	////Vertex Texture Coords
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BufferVertex),
	//	(GLvoid*)offsetof(BufferVertex, TexCoords));
	//
	//glBindVertexArray(0);
}

void BufferManager::addBuffer()
{
	glBindVertexArray(this->VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObject);

	glBufferData(GL_ARRAY_BUFFER, this->vertexBuffer.size()* sizeof(BufferVertex),
		&this->vertexBuffer[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesBuffer.size() * sizeof(GLuint),
		&this->indicesBuffer[0], GL_STATIC_DRAW);

	//Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BufferVertex),
		(GLvoid*)0);

	//Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BufferVertex),
		(GLvoid*)offsetof(BufferVertex, Normal));

	//Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BufferVertex),
		(GLvoid*)offsetof(BufferVertex, TexCoords));

	//Vertex Color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(BufferVertex),
		(GLvoid*)offsetof(BufferVertex, Color));
}

void BufferManager::addBufferData(std::vector<BufferVertex> vertices, std::vector<GLuint> indices, std::vector<BufferTexture> textures)
{
	vertexBuffer = vertices;
	indicesBuffer = indices;
	this->textures = textures;

	this->addBuffer();
}

void BufferManager::drawBuffer(Shader shader)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;

	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + 1);

		std::stringstream ss;
		std::string number;
		std::string name = this->textures[i].type;
		if (name == "texture_diffuse")
		{
			ss << diffuseNr++;
		}

		else if (name == "texture_specular")
		{
			ss << specularNr++;
		}

		number = ss.str();

		glUniform1i(glGetUniformLocation(shader.GetShaderProgram(), ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}

	glUniform1f(glGetUniformLocation(shader.GetShaderProgram(), "material.shininess"), 16.0f);

	//draw mesh
	glBindVertexArray(this->VertexArrayObject);
	glDrawElements(GL_TRIANGLES, this->indicesBuffer.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void BufferManager::testBuffer()
{
	//create the data
	std::vector<BufferVertex> v;

	BufferVertex BV1;
	BufferVertex BV2;
	BufferVertex BV3;
	BufferVertex BV4;

	v.push_back(BV1);
	v.push_back(BV2);
	v.push_back(BV3);

	for (int i = 0; i < 3; i++)
	{
		//std::srand(std::time(0));
		tempColor++;

		if (tempColor > 255)
		{
			tempColor = 0;
		}
		

		if(i == 0)
		v[i].Position = glm::vec3(-5.2f - 4.8, -5.4f - 4.6, -1.2f + 8.8f);
		else if (i == 1)
			v[i].Position = glm::vec3(10.0f + 0.0f, 1.4f + 8.6f, -1.2f + 8.8f);
		else if (i == 2)
			v[i].Position = glm::vec3(1.2f + 1.0f, -11.4f + 1.4f, 7.2f + 2.0f);

		v[i].Normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v[i].TexCoords = glm::vec2(1.0f, 0.0f);
		std::cout << "tempColor: " << tempColor << std::endl;
		v[i].Color = glm::vec3(0, 0, tempColor);
	}

	GLuint indicesArray[9] = { 1, 2, 3, 1, 2, 3, 1, 2, 3 };	

	std::vector<GLuint> testIndices;

	for (int i = 0; i < 9; i++)
		testIndices.push_back(indicesArray[i]);

		std::vector<BufferTexture> tex;

		BufferTexture bt1;
		BufferTexture bt2;
		BufferTexture bt3;
		bt1.id = 1;
		bt1.type = "texture_diffuse";

		bt2.id = 1;
		bt2.type = "texture_diffuse";

		bt2.id = 1;
		bt2.type = "texture_diffuse";

		tex.push_back(bt1);
		tex.push_back(bt2);
		tex.push_back(bt3);

		//add the data
		addBufferData(v, testIndices, tex);

		//load tempShader
		Shader testShader;

		//tempShader init
		testShader.Init();

		//draw what is in the buffer
		drawBuffer(testShader);

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
		"in vec3 color; \n"
		"out vec4 Fcolor;\n"
		"void main()\n"
		"{\n"
		"Fcolor = vec4(color, 1.0f);\n"
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


//void BufferManager::addVertexData(GLfloat *data, GLsizei size)
//{	
//	glBindBuffer(GL_ARRAY_BUFFER, vertexbufId);
//	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	//pos
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	//color
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	//tex Coord
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	vertexBuffer.push_back(vertexbufId);
//	
//}

//void BufferManager::addIndexData(GLuint *data, GLuint *size)
//{
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufID);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLuint), size, GL_STATIC_DRAW);
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	indexBuffer.push_back(indexbufID);
//}

//void BufferManager::drawBuffer(std::vector<GLuint> buffer)
//{	
//	
//	//Clear the backbuffer and the depth-buffer
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//	glUseProgram(shaderProgram);
//
//	
//	for (int i = 0; i < vertexBuffer.size() - 1; i++)
//	{
//		glBindVertexArray(vertexBuffer);
//		glDrawElements(GL_TRIANGLES, vertexBuffer.size(), GL_UNSIGNED_INT, 0); //reinterpret_cast<GLvoid*>(0));	
//	}
//
//	glBindVertexArray(0);
//
//}

//std::vector<GLuint> BufferManager::getBuffer(std::string bufferName)
//{
//
//	if (bufferName == "vertexbuffer" || bufferName == "Vertexbuffer" || bufferName == "vertexBuffer" || bufferName == "VertexBuffer" || bufferName == "vertex buffer" || bufferName == "Vertex Buffer" || bufferName == "vertex Buffer" || bufferName == "Vertex buffer")
//	{
//		return vertexBuffer;
//	}
//	else if (bufferName == "indexBuffer" || bufferName == "indexbuffer" || bufferName == "Indexbuffer" || bufferName == "IndexBuffer" || bufferName == "Index Buffer" || bufferName == "index buffer" || bufferName == "Index buffer" || bufferName == "index Buffer")
//	{
//		return indexBuffer;
//	}
//	//else
//	//{
//	//	return nullptr;
//	//}
//} //rikki
