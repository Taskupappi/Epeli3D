#include "BufferManager.h"

BufferManager::BufferManager()
{
	initBuffers();

	////Testbench stuff
	//tempShader init
	
	testShader.Init("../data/shaders/VertexShaderLightSource.glvs", "../data/shaders/FragmentShaderLightSource.glfs");
	testLampShader.Init("../data/shaders/VertexShaderLamp.glvs", "../data/shaders/FragmentShaderLamp.glfs");
	
	//camera
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 15.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	cam = new Camera();

	cam->setShader(&testShader);
	cam->setView(cameraPos, cameraPos + cameraFront, cameraUp);

	angle = 0;
	////
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
	glGenBuffers(1, &NormalBufferObject);
}

void BufferManager::addBufferData(std::vector<BufferVertex> vertices, std::vector<GLuint> indices, std::vector<BufferTexture> textures)
{
	//should sort indices in some way
	//will cause problems in the future otherwise

	vertexBuffer.insert(vertexBuffer.end(), vertices.begin(), vertices.end());
	indicesBuffer.insert(indicesBuffer.end(), indices.begin(), indices.end());
	this->textures.insert(this->textures.end(), textures.begin(), textures.end()); //not needed here

	//int blockn = 1;
	//for (auto itvertexBuffer = vertexBuffer.begin(); itvertexBuffer != vertexBuffer.end(); itvertexBuffer++)
	//{
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
	//}
	//
	//std::cout << "////////////////IndexBuffer///////////////// \n";
	//for (auto itindexBuffer = indicesBuffer.begin(); itindexBuffer != indicesBuffer.end(); itindexBuffer++)
	//{
	//	std::cout << *itindexBuffer << "\n";
	//}
	//std::cout << "///////////////////////////////////// \n";

	this->addBuffer();
}

void BufferManager::setBufferData(std::vector<BufferVertex> vertices, std::vector<GLuint> indices, std::vector<BufferTexture> textures)
{
	//should sort indices in some way
	//will cause problems in the future otherwise
	vertexBuffer.clear();
	indicesBuffer.clear();
	this->textures.clear();

	vertexBuffer.insert(vertexBuffer.begin(), vertices.begin(), vertices.end());
	indicesBuffer.insert(indicesBuffer.begin(), indices.begin(), indices.end());
	this->textures.insert(this->textures.begin(), textures.begin(), textures.end()); //not needed here

	//int blockn = 1;
	//for (auto itvertexBuffer = vertexBuffer.begin(); itvertexBuffer != vertexBuffer.end(); itvertexBuffer++)
	//{
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
	//}
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

void BufferManager::drawTestBuffer(int x)
{
	//draw what is in the buffer

	if (x == TEST)
		drawBuffer(testShader);
	else if (x == LAMP)
		drawBuffer(testLampShader);
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
	////Model loading
	/*model = new Object3D("../data/Resource/Models/nanosuit2.3ds");
	

	std::vector<BufferVertex> v3D;
	std::vector<GLuint> indices3D;

	std::vector<Mesh>::iterator *it;

	for (it = model->get3DMesh().begin; it != model->get3DMesh().end; it++)
	{
		v3D.push_back((*it)->vertices);
		indices3D.push_back((*it)->indices);
	}*/
	/////

	////first Cube
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

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	std::vector<BufferVertex> v;
	std::vector<BufferTexture> tex1;

	//declare outside of the for loop to temporary fix a bug with the buffer
	BufferVertex BV1;

	for (int i = 0; i < 36; i++)
	{
		//BufferVertex BV1; temorarily outside of the for loop

		BV1.Position = glm::vec3(vertices[i * 5], vertices[i * 5 + 1], vertices[i * 5 + 2]);
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

		//BV1.Color = glm::vec3(0.0f, 0.0f, 0.0f);

		v.push_back(BV1);

		BufferTexture bt;
		bt.id = 1;
		bt.type = "texture_diffuse";

		tex1.push_back(bt);
	}

	std::vector<GLuint> testIndices;
	//GLushort cubeIndices[] = {
	//	// front
	//	0, 1, 2,
	//	2, 3, 0,
	//	// top
	//	1, 5, 6,
	//	6, 2, 1,
	//	// back
	//	7, 6, 5,
	//	5, 4, 7,
	//	// bottom
	//	4, 0, 3,
	//	3, 7, 4,
	//	// left
	//	4, 5, 1,
	//	1, 0, 4,
	//	// right
	//	3, 2, 6,
	//	6, 7, 3,
	//};
	//
	//for (int i = 0; i < 36; i++)
	//{
	//	testIndices.push_back(cubeIndices[i]);
	//}
		
	for (int i = 0; i < 36; i++)
		testIndices.push_back(i);

	//v.push_back(BV1);
	
	addBufferData(v, testIndices, tex1);

	//drawTestBuffer(TEST);
	/////

	////multiple cubes
	int numCubes = 4;
	std::vector<BufferVertex> vcopy;
	std::vector<BufferTexture> tex1copy;
	std::vector<GLuint> testIndicescopy;

	for (int i = 0; i < numCubes; i++)
	{
		vcopy.insert(vcopy.end(), v.begin(), v.end());
		tex1copy.insert(tex1copy.end(), tex1.begin(), tex1.end());	
	}	
	
	for (int i = 0; i < 36 * numCubes; i++)
	{
		if (testIndicescopy.size() < 36)
			testIndicescopy.push_back(i + testIndices.size());
		else if (testIndicescopy.size() < 72)
			testIndicescopy.push_back(i + testIndices.size());
		else if (testIndicescopy.size() < 108)
			testIndicescopy.push_back(i + testIndices.size());
		else if (testIndicescopy.size() < 144)
			testIndicescopy.push_back(i + testIndices.size());
		else
		int y = 0;
		/*else
			testIndicescopy.push_back(i + testIndicescopy.size());*/
	}

	//for (int i = 36; i < 72; i++)
	//	vcopy[i].Position += 2;
	//
	////
	//multiple cubes
	//addBufferData(vcopy, testIndicescopy, tex1copy);
	//
	//single cube
	//addBufferData(v, testIndices, tex1);

	int multiplier = 0;
	multiplier = 0;

	for (int i = 0; i < 36 * numCubes; i++)
	{
		if (remainder(i, 36) == 0)
			multiplier -= 2;			

		vcopy[i].Position.x += multiplier;
		//if (i < 36)
		//vcopy[i].Position += multiplier;
		//else if (i < 36 * 2)
		//{
		//	vcopy[i].Position.x += multiplier + 2;
		//}
		//else if (i < 36 * 3)
		//{
		//	vcopy[i].Position.x += multiplier + 4;
		//}
		//else if (i < 36 * 4)
		//{
		//	vcopy[i].Position.x += multiplier + 6;
		//}		

		//testIndicescopy[i] += 36;
		vcopy[i].Color = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	//temporary fix
	//to fix a bug
	//vcopy.push_back(BV1);
	
	vcopy.push_back(BV1);

	addBufferData(vcopy, testIndicescopy, tex1);

	drawTestBuffer(TEST);
	////

	//lighting
	//GLuint lighting;
	//newVAO(lighting);
}

void BufferManager::testBoxUpdate()
{
	getShader(TEST).Use();

	// Create transformations
	/*glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;*/
	//
	////Transform calculations
	//cam->rotate(180, glm::vec3(0.5f, 1.0f, 0.0f));
	//cam->rotate((GLfloat)angle / 3.14/180, glm::vec3(0.5f, 1.0f, 0.0f));
	//model = glm::rotate(model, (GLfloat)rotation / 10, glm::vec3(0.5f, 1.0f, 0.0f));
	//
	//cam->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//
	//cam->setProjection(45, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
	//projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

	rotation += 0.02;
	if (rotation > 360)
	{
		rotation = 0;
	}

	// Camera/View transformation
	GLfloat radius = 2.0f;
	GLfloat camX = 2; // sin(rotation / 3) * radius;
	GLfloat camY = 4; //cos(rotation / 8) * radius;
	GLfloat camZ =  cos(rotation / 3) * radius;

	cam->setView(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	/*view = glm::lookAt(glm::vec3(camX, 0, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/

	// Projection 
	cam->setProjection(90.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
	/*projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);*/

	// Get uniform locations
	/*Objects get these from a camera and send them to the shader instead of doing new ones*/
	GLint boxModelLoc = glGetUniformLocation(getShader(TEST).GetShaderProgram(), "model");
	GLint boxViewLoc = glGetUniformLocation(getShader(TEST).GetShaderProgram(), "view");
	GLint boxProjLoc = glGetUniformLocation(getShader(TEST).GetShaderProgram(), "projection");

	// Pass uniform locations to the shaders
	glUniformMatrix4fv(boxModelLoc, 1, GL_FALSE, glm::value_ptr(cam->getModel()));
	glUniformMatrix4fv(boxViewLoc, 1, GL_FALSE, glm::value_ptr(cam->getView()));
	glUniformMatrix4fv(boxProjLoc, 1, GL_FALSE, glm::value_ptr(cam->getProjection()));

	////temporary rotation for a demo cube
	//glPushMatrix();
	//glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(0.0f, 0.0f, 1.0f, 1.0f);
	//rotation += 0.25f;
	//if (rotation > 360)
	//	rotation = 0;

	//buff->drawBuffer(buff->getBuffer(nam));

	//cam->setPosition(cubePositions[0]);
	//cam->rotate(angle, glm::vec3(1.0f, 0.3f, 0.5f));
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cam->getModel()));

	model = glm::translate(model, glm::vec3(.0f, .0f, .0f));
	//model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(boxModelLoc, 1, GL_FALSE, glm::value_ptr(model));

	angle = 0.2f;
	//for (int i = 0; i < 10; i++)
	//{		
	//	model = glm::translate(model, cubePositions[i]);
	//	//model = glm::rotate(model, angle, glm::vec3(1.0f, 1.0f, 0.0f));
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//}	
}

void BufferManager::newVAO(const GLuint vao)
{
	VertexArrayObject = vao;
	glGenVertexArrays(1, &VertexArrayObject);
	addBuffer();
	//glBindVertexArray(VertexArrayObject);
}

Camera* BufferManager::getCamera()
{
	return cam;
}

Shader BufferManager::getShader(int x)
{
	if (x == TEST)
		return testShader;
	else if (x == LAMP)
		return testLampShader;	
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