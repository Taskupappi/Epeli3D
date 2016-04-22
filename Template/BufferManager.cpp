#include "BufferManager.h"

BufferManager::BufferManager()
{
	//initBuffers();

	////Testbench stuff
	//3d model
	model3D = Object3D("../data/Resource/Models/Shark.stl");	

	//shader manager
	shaderManager = new ShaderManager();

	shaderManager->createShader("../data/shaders/VertexShaderLamp.glvs", "../data/shaders/FragmentShaderLamp.glfs", "testLampShader");
	shaderManager->createShader("../data/shaders/VertexShaderLightSource.glvs", "../data/shaders/FragmentShaderLightSource.glfs", "testShader");
	shaderManager->setActiveShader("testShader");
	
	//camera
	cam = new Camera();
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
	/*if (vertexBuffer.size() != 0)
	{

	}*/
}

void BufferManager::initBuffers(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
	GLuint VertexArrayObject;
	glGenVertexArrays(1, &VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);
	glGenBuffers(1, &ElementBufferObject);
	
	//VAO bind
	glBindVertexArray(VertexArrayObject);

	//VBO bind & buffer data
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(Vertex),
		&vertices[0], GL_DYNAMIC_DRAW);

	//EBO bind & buffer data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
		&indices[0], GL_DYNAMIC_DRAW);

	//Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);

	//Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Normal));

	//Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, TexCoords));

	//Vertex Color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Color));

	VertexArrayObjects.push_back(VertexArrayObject);

	glBindVertexArray(0);
}

void BufferManager::addBufferData(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{	
	initBuffers(vertices, indices);
	 
	std::vector<Vertex> objVertexes;
	std::vector<GLuint> objIndices;

	objVertexes.insert(objVertexes.end(), vertices.begin(), vertices.end());
	objIndices.insert(objIndices.end(), indices.begin(), indices.end());

	this->vertexes.push_back(objVertexes);
	this->indices.push_back(objIndices);
}

void BufferManager::drawBuffer(Shader* shader)
{
	int elementN = 0;
	VAOIter = VertexArrayObjects.begin();
	
	//one loop == one object drawn
	for (VAOIter; VAOIter != VertexArrayObjects.end(); VAOIter++)
	{		
		elementN = std::distance(VertexArrayObjects.begin(), VAOIter);
		glBindVertexArray((*VAOIter));
		glDrawElements(GL_TRIANGLES, this->indices[elementN].size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

////NOT FUNCTIONING/////
void BufferManager::setBufferData(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
	initBuffers(vertices, indices);

	std::vector<Vertex> vt{};
	std::vector<GLuint> it{};

	//objVertexes.swap(vt);
	//objIndices.swap(it);

	//objVertexes.insert(objVertexes.begin(), vertices.begin(), vertices.end());
	//objIndices.insert(objIndices.begin(), indices.begin(), indices.end());

	this->addVertexArrayObject();
}

void BufferManager::addVertexArrayObject()
{
	//GLuint newVAO;
	//glGenVertexArrays(1, &newVAO);
	//glBindVertexArray(newVAO);

	//glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObject);
	//glBufferData(GL_ARRAY_BUFFER, this->objVertexes.size()* sizeof(Vertex),
	//	&this->objVertexes[0], GL_DYNAMIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBufferObject);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->objVertexes.size() * sizeof(GLuint),
	//	&this->objVertexes[0], GL_DYNAMIC_DRAW);

	////Vertex Positions
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)0);

	////Vertex Normals
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)offsetof(Vertex, Normal));

	////Vertex Texture Coords
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)offsetof(Vertex, TexCoords));

	////Vertex Color
	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)offsetof(Vertex, Color));

	//VertexArrayObjects.push_back(newVAO);

	//glBindVertexArray(0);
}
//////



//TESTBENCH STUFF
void BufferManager::initTest()
{
	testBox();
}

void BufferManager::testBox()
{
	////Model loading
	std::vector<Vertex> v3D;
	std::vector<GLuint> indices3D;
	
	std::vector<Mesh>::iterator modelIter;
	std::vector<Vertex>::iterator vertexIter;
	std::vector<GLuint>::iterator indicesIter;
	
	std::vector<Mesh> mesh;
	mesh = model3D.getMeshVec();

	for (modelIter = model3D.getMeshVec().begin(); modelIter != model3D.getMeshVec().end(); modelIter++)
		{
			for (vertexIter = modelIter->vertices.begin(); vertexIter != modelIter->vertices.end(); vertexIter++)
			{
				v3D.push_back((*vertexIter));
			}	

			for (indicesIter = modelIter->indices.begin(); indicesIter != modelIter->indices.end(); indicesIter++)
			{
				indices3D.push_back((*indicesIter));
			}
		}
		
	//addBufferData(v3D, indices3D);
	//setBufferData(vcopy, testIndicescopy);
	//drawTestBuffer();
	////end of 3d model loading//

	//TEST TRIANGLE FOR DEBUG
	std::vector<Vertex> ver;
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	for (int i = 0; i < 3; i++)
	{
		Vertex v;
		v.Position.x = vertices[i * 3];
		v.Position.x = vertices[i * 3 + 1];
		v.Position.x = vertices[i * 3 + 2];
		v.Color = glm::vec3(122,122,122);
		ver.push_back(v);
	}

	std::vector<GLuint> inds;
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	for (int i = 0; i < 6; i++)
	{
		inds.push_back(indices[i]);
	}

	addBufferData(ver, inds);
	drawTestBuffer();
	//

	/*
	////first Cube
	//GLfloat vertices[] = {
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	//	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	//	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	//	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

	//	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	//	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	//	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	//	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	//	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	//	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	//	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	//	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	//};
	//glm::vec3 cubePositions[] = {
	//	glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(2.0f, 5.0f, -15.0f),
	//	glm::vec3(-1.5f, -2.2f, -2.5f),
	//	glm::vec3(-3.8f, -2.0f, -12.3f),
	//	glm::vec3(2.4f, -0.4f, -3.5f),
	//	glm::vec3(-1.7f, 3.0f, -7.5f),
	//	glm::vec3(1.3f, -2.0f, -2.5f),
	//	glm::vec3(1.5f, 2.0f, -2.5f),
	//	glm::vec3(1.5f, 0.2f, -1.5f),
	//	glm::vec3(-1.3f, 1.0f, -1.5f)
	//};

	//GLfloat vertices2[] = {
	//	0.5f, 0.5f, 0.0f,  // Top Right
	//	0.5f, -0.5f, 0.0f,  // Bottom Right
	//	-0.5f, -0.5f, 0.0f,  // Bottom Left
	//	-0.5f, 0.5f, 0.0f   // Top Left 
	//};
	//GLuint indices2[] = {  // Note that we start from 0!
	//	0, 1, 3,  // First Triangle
	//	1, 2, 3   // Second Triangle
	//};



	////some normals, dunno
	//std::vector<glm::vec3> normals;			
	//normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	//normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	//normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	//normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	//normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	//normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));

	//std::vector<Vertex> v;

	//Vertex BV1;
	//for (int i = 0; i < 36; i++)
	//{
	//	//BufferVertex BV1; temorarily outside of the for loop

	//	BV1.Position = glm::vec3(vertices[i * 5], vertices[i * 5 + 1], vertices[i * 5 + 2]);
	//	
	//	if (i < 36)
	//		BV1.Normal = normals[5];
	//	if (i < 30)
	//		BV1.Normal = normals[4];
	//	if (i < 24)
	//		BV1.Normal = normals[3];
	//	if (i < 18)
	//		BV1.Normal = normals[2];
	//	if (i < 12)
	//		BV1.Normal = normals[1];
	//	if (i < 6)
	//		BV1.Normal = normals[0];

	//	BV1.TexCoords = glm::vec2(vertices[i * 5 + 3], vertices[i * 5 + 4]);
	//	
	//	if (i < 36)
	//		BV1.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	//	if (i < 30)
	//		BV1.Color = glm::vec3(1.0f, 1.0f, 0.0f);
	//	if(i < 24)
	//		BV1.Color = glm::vec3(1.0f, 0.0f, 1.0f);
	//	if (i < 18)
	//		BV1.Color = glm::vec3(1.0f, 0.0f, 0.0f);
	//	if (i < 12)
	//		BV1.Color = glm::vec3(0.0f, 1.0f, 0.0f);
	//	if (i < 6)
	//		BV1.Color = glm::vec3(0.0f, 0.0f, 1.0f);

	//	//BV1.Color = glm::vec3(0.0f, 0.0f, 0.0f);

	//	v.push_back(BV1);
	//}

	//std::vector<GLuint> testIndices;
	//	
	//for (int i = 0; i < 36; i++)
	//	testIndices.push_back(i);

	////v.push_back(BV1);
	//
	////setBufferData(v, testIndices, tex1);
	////setBufferData(v3D, indices3D, tex1);

	////drawTestBuffer();
	///////

	//////multiple cubes
	//int numCubes = 4;
	//std::vector<Vertex> vcopy;
	//std::vector<GLuint> testIndicescopy;
	//
	//for (int i = 0; i < 36 * numCubes; i++)
	//{
	//	if (testIndicescopy.size() < 36)
	//		testIndicescopy.push_back(i + testIndices.size());
	//	else if (testIndicescopy.size() < 72)
	//		testIndicescopy.push_back(i + testIndices.size());
	//	else if (testIndicescopy.size() < 108)
	//		testIndicescopy.push_back(i + testIndices.size());
	//	else if (testIndicescopy.size() < 144)
	//		testIndicescopy.push_back(i + testIndices.size());
	//	else
	//	int y = 0;
	//	else
	//		testIndicescopy.push_back(i + testIndicescopy.size());
	//}

	//////

	////multiple cubes
	////addBufferData(vcopy, testIndicescopy, tex1copy);
	////
	////single cube
	////addBufferData(v, testIndices, tex1);

	//int multiplier = 0;
	//multiplier = 0;

	//for (int i = 0; i < 36 * numCubes; i++)
	//{
	//	if (remainder(i, 36) == 0)
	//		multiplier -= 2;			

	//	vcopy[i].Position.x += multiplier;
	//	vcopy[i].Color = glm::vec3(1.0f, 1.0f, 1.0f);
	//}
	////vcopy.push_back(BV1);

	////addBufferData(vcopy, testIndicescopy);
	////setBufferData(vcopy, testIndicescopy);
	////drawTestBuffer();

	////lighting
	////GLuint lighting;
	////newVAO(lighting);	
*/
}

void BufferManager::testBoxUpdate()
{
	shaderManager->useActiveShader();

	GLint lightPosLoc = glGetUniformLocation(shaderManager->getActiveShader()->getShaderProgram(), "lightPos");
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

	rotation += 2.0f;
	if (rotation > 36000)
	{
		rotation = 0;
	}

	// Get uniform locations
	/*Objects get these from a camera and send them to the shader instead of doing new ones*/
	GLint boxModelLoc = glGetUniformLocation(shaderManager->getActiveShader()->getShaderProgram(), "model");
	GLint boxViewLoc = glGetUniformLocation(shaderManager->getActiveShader()->getShaderProgram(), "view");
	GLint boxProjLoc = glGetUniformLocation(shaderManager->getActiveShader()->getShaderProgram(), "projection");
	
	glm::mat4 tempView;

	tempView = glm::mat4(0);

	//temp model matrix until game object class is done
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	GLfloat angle = 20.0f;
	model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
	glUniformMatrix4fv(boxModelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 projection;
	//fov, width / height, near, far
	projection = glm::perspective(45.0f, (float)800 / (float)600, 0.1f, 1000.0f);
	glUniformMatrix4fv(boxViewLoc, 1, GL_FALSE, glm::value_ptr(cam->getViewMatrix())); //cam->getViewMatrix() instead of tempView
	glUniformMatrix4fv(boxProjLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void BufferManager::drawTestBuffer()
{
	//draw what is in the buffer
	drawBuffer(shaderManager->getActiveShader());
}

Camera* BufferManager::getCamera()
{
	return cam;
}