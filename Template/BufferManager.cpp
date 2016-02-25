#include "BufferManager.h"

BufferManager::BufferManager()
{
	//initShaders();

	initBuffers();

	//Testbench stuff
	//tempShader init
	testShader.Init();

	//camera
	cam  = new Camera();
	cam->init();
	
	//
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
	glGenVertexArrays(1, &this->VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);
	glGenBuffers(1, &ElementBufferObject);
}

void BufferManager::addBufferData(std::vector<BufferVertex> vertices, std::vector<GLuint> indices, std::vector<BufferTexture> textures)
{
	vertexBuffer.insert(vertexBuffer.end(), vertices.begin(), vertices.end());
	indicesBuffer.insert(indicesBuffer.end(), indices.begin(), indices.end());
	this->textures.insert(this->textures.end(), textures.begin(), textures.end());
	
	int blockn = 1;
	for (auto itvertexBuffer = vertexBuffer.begin(); itvertexBuffer != vertexBuffer.end(); itvertexBuffer++)
	{
	//	std::cout << "//////////////Vertex block of data: "<< blockn <<  " //////////// \n";
	//	std::cout << "\n Position \n";
	//	std::cout << (itvertexBuffer)->Position.x << "\n";
	//	std::cout << (itvertexBuffer)->Position.y << "\n";
	//	std::cout << (itvertexBuffer)->Position.z << "\n";
	//	std::cout << "\n Normal \n";
	//	std::cout << (itvertexBuffer)->Normal.x << "\n";
	//	std::cout << (itvertexBuffer)->Normal.y << "\n";
	//	std::cout << (itvertexBuffer)->Normal.z << "\n";
	//	std::cout << "\n TexCoords \n";
	//	std::cout << (itvertexBuffer)->TexCoords.x << "\n";
	//	std::cout << (itvertexBuffer)->TexCoords.y << "\n";
		//std::cout << "\n Color \n";
		//std::cout << (itvertexBuffer)->Color.x << "\n";
		//std::cout << (itvertexBuffer)->Color.y << "\n";
		//std::cout << (itvertexBuffer)->Color.z << "\n";
		//std::cout << "\n";
	//	blockn++;
	//	std::cout << "///////////////////////////////////// \n";
	}
	//
	//std::cout << "////////////////IndexBuffer///////////////// \n";
	//for (auto itindexBuffer = indicesBuffer.begin(); itindexBuffer != indicesBuffer.end(); itindexBuffer++)
	//{
	//	std::cout << *itindexBuffer << "\n";
	//}
	//std::cout << "///////////////////////////////////// \n";

	this->addBuffer();
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

void BufferManager::testBuffer()
{
	//draw what is in the buffer
	drawBuffer(testShader);
}

void BufferManager::drawBuffer(Shader shader)
{

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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

	//Testbench
	//camera
	MVP = cam->getViewMatrix();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);


	//
}

void BufferManager::initTest()
{
	/*
	////create the data
	//std::vector<BufferVertex> v;

	//BufferVertex BV1;
	//BufferVertex BV2;
	//BufferVertex BV3;
	//BufferVertex BV4;

	//v.push_back(BV1);
	//v.push_back(BV2);
	//v.push_back(BV3);

	//for (int i = 0; i < 3; i++)
	//{
	//	pos += 0.0f;
	//	//std::srand(std::time(0));
	//	tempColor += 0.001;

	//	if (tempColor > 1)
	//	{
	//		tempColor = 0;
	//	}

	//	if (i == 0)
	//		v[i].Position = glm::vec3(0.0f + pos, 0.0f, 1.0f);
	//	else if (i == 1)
	//		v[i].Position = glm::vec3(0.5f + pos, 0.0f + pos, 1.0f);
	//	else if (i == 2)
	//		v[i].Position = glm::vec3(0.5f + pos, 0.5f, 1.0f);

	//	v[i].Normal = glm::vec3(0.0f, 1.0f, 0.0f);
	//	v[i].TexCoords = glm::vec2(1.0f, 0.0f);
	//	//std::cout << "tempColor: " << tempColor << std::endl;
	//	v[i].Color = glm::vec3(tempColor + 0.8, 1, 1);
	//}

	//GLuint indicesArray[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8 };

	//std::vector<GLuint> testIndices;

	//for (int i = 0; i < 9; i++)
	//	testIndices.push_back(indicesArray[i]);

	//std::vector<BufferTexture> tex;

	//BufferTexture bt1;
	//BufferTexture bt2;
	//BufferTexture bt3;
	//bt1.id = 1;
	//bt1.type = "texture_diffuse";

	//bt2.id = 1;
	//bt2.type = "texture_diffuse";

	//bt3.id = 1;
	//bt3.type = "texture_diffuse";

	//tex.push_back(bt1);
	//tex.push_back(bt2);
	//tex.push_back(bt3);

	////add the data
	////addBufferData(v, testIndices, tex);

	////load tempShader
	////Shader testShader;

	/////////////////////////////////////////////////////////////
	////add another block of data

	////create the data
	//std::vector<BufferVertex> v1;

	//BufferVertex BV11;
	//BufferVertex BV21;
	//BufferVertex BV31;
	//BufferVertex BV41;

	//v1.push_back(BV11);
	//v1.push_back(BV21);
	//v1.push_back(BV31);	

	//for (int i = 0; i < 3; i++)
	//{
	//
	//	//std::srand(std::time(0));
	//	tempColor += 0.001;

	//	if (tempColor > 1)
	//	{
	//		tempColor = 0;
	//	}

	//	if (i == 0)
	//		v1[i].Position = glm::vec3(-0.9f - pos, 0.9f, 1.0f);
	//	else if (i == 1)
	//		v1[i].Position = glm::vec3(-0.9f - pos, -0.9f- pos, 1.0f);
	//	else if (i == 2)
	//		v1[i].Position = glm::vec3(0.0f - pos, 0.0f, 1.0f);

	//	v1[i].Normal = glm::vec3(0.0f, 1.0f, 0.0f);
	//	v1[i].TexCoords = glm::vec2(1.0f, 0.0f);
	//	v1[i].Color = glm::vec3(tempColor, 0, 0.7);
	//}
	//
	//GLuint indicesArray1[9] = { 9,10, 11, 12, 13, 14, 15, 16, 17};

	//std::vector<GLuint> testIndices1;

	//for (int i = 0; i < 9; i++)
	//	testIndices1.push_back(indicesArray1[i]);

	//std::vector<BufferTexture> tex1;

	//BufferTexture bt11;
	//BufferTexture bt21;
	//BufferTexture bt31;
	//bt11.id = 1;
	//bt11.type = "texture_diffuse";

	//bt21.id = 1;
	//bt21.type = "texture_diffuse";

	//bt31.id = 1;
	//bt31.type = "texture_diffuse";

	//tex1.push_back(bt11);
	//tex1.push_back(bt21);
	//tex1.push_back(bt31);

	////add the data
	//addBufferData(v, testIndices, tex);
	//addBufferData(v1, testIndices1, tex1);
	*/

	
	
	testBox();
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

void BufferManager::testBox()
{

		GLfloat vertices[] = {
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
		};

	std::vector<BufferVertex> v;
	std::vector<BufferTexture> tex1;

	for (int i = 0; i <= 36; i++)
	{
		BufferVertex BV1;

		BV1.Position = glm::vec3(vertices[i*5], vertices[i*5 + 1], vertices[i*5 + 2]);
		BV1.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
		BV1.TexCoords = glm::vec2(vertices[i * 5 + 3], vertices[i * 5 + 4]);
		
		if (i < 36)
			BV1.Color = glm::vec3(1.0f, 1.0f, 1.0f);
		if (i < 30)
			BV1.Color = glm::vec3(1.0f, 1.0f, 0.0f);
		if (i < 24)
			BV1.Color = glm::vec3(1.0f, 0.0f, 1.0f);
		if (i < 18)
			BV1.Color = glm::vec3(1.0f, 0.0f, 0.0f);
		if (i < 12)
			BV1.Color = glm::vec3(0.0f, 1.0f, 0.0f);
		if (i < 6)
			BV1.Color = glm::vec3(0.0f, 0.0f, 1.0f);

		v.push_back(BV1);
		
		BufferTexture bt;
		bt.id = 1;
		bt.type = "texture_diffuse";

		tex1.push_back(bt);
	}

	GLuint indicesArray1[36] = {};

	std::vector<GLuint> testIndices;

	for (int i = 0; i < 36; i++)
		testIndices.push_back(i);


	addBufferData(v, testIndices, tex1);

}

Shader BufferManager::getShader()
{
	return testShader;
}