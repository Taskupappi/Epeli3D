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
	

	angle = 0;
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
	this->textures.insert(this->textures.end(), textures.begin(), textures.end()); //not needed here
	
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
	//GLuint diffuseNr = 1;
	//GLuint specularNr = 1;
	//
	//for (GLuint i = 0; i < this->textures.size(); i++)
	//{
	//	glActiveTexture(GL_TEXTURE0 + 1);
	//
	//	std::stringstream ss;
	//	std::string number;
	//	std::string name = this->textures[i].type;
	//	if (name == "texture_diffuse")
	//	{
	//		ss << diffuseNr++;
	//	}
	//
	//	else if (name == "texture_specular")
	//	{
	//		ss << specularNr++;
	//	}
	//
	//	number = ss.str();
	//
	//	glUniform1i(glGetUniformLocation(shader.GetShaderProgram(), ("material." + name + number).c_str()), i);
	//	glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	//}
	//
	//glUniform1f(glGetUniformLocation(shader.GetShaderProgram(), "material.shininess"), 16.0f);
	
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

void BufferManager::initTest()
{
	testBox();
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

	//multiple cubes
	std::vector<BufferVertex> vcopy;
	std::vector<BufferTexture> tex1copy;

	for (int i = 0; i < 10; i++)
	{
		vcopy.insert(vcopy.end(), v.begin(), v.end());
		tex1copy.insert(tex1copy.end(), tex1.begin(), tex1.end());		

		for (int i = 0; i < 36; i++)
			testIndices.push_back(i);
	}
	////
	//multiple cubes
	addBufferData(vcopy, testIndices, tex1copy);

	//single cube
	//addBufferData(v, testIndices, tex1);

}

void BufferManager::testBoxUpdate()
{
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f)/*,
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)*/
	};	

	getShader().Use();

	// Create transformations
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	//Transform calculations
	model = glm::rotate(model, (GLfloat)rotation / 10, glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

	// Camera/View transformation
	GLfloat radius = 2.0f;
	GLfloat camX = sin(rotation / 4) * radius;
	GLfloat camZ = cos(rotation / 4) * radius;
	view = glm::lookAt(glm::vec3(camX, 0, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Projection 
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

	// Get uniform locations
	GLint modelLoc = glGetUniformLocation(getShader().GetShaderProgram(), "model");
	GLint viewLoc = glGetUniformLocation(getShader().GetShaderProgram(), "view");
	GLint projLoc = glGetUniformLocation(getShader().GetShaderProgram(), "projection");

	// Pass uniform locations to the shaders
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	////temporary rotation for a demo cube
	//glPushMatrix();
	//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(0.0f, 0.0f, 1.0f, 1.0f);
	//rotation += 0.25f;
	//if (rotation > 360)
	//	rotation = 0;

	//buff->drawBuffer(buff->getBuffer(nam));
	

	model = glm::translate(model, cubePositions[0]);
	if (!rewind)
	{
		angle += 0.02f;
		if (angle = 720)
			rewind = true;
	}
	else if (rewind)
	{
		angle -= 0.02f;
		if (angle < 0)
			rewind = false;
	}


	model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));	

}

Shader BufferManager::getShader()
{
	return testShader;
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