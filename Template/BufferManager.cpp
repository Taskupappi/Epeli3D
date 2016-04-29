#include "BufferManager.h"

BufferManager::BufferManager()
{
	//initBuffers();
	//
	////Testbench stuff
	//3d model
	//model3D = Object3D("../data/Resource/Models/Shark.stl");	
	//
	//shader manager
	//shaderManager = new ShaderManager();
	//
	//shaderManager->createShader("../data/shaders/VertexShaderLamp.glvs", "../data/shaders/FragmentShaderLamp.glfs", "testLampShader");
	//shaderManager->createShader("../data/shaders/VertexShaderLightSource.glvs", "../data/shaders/FragmentShaderLightSource.glfs", "testShader");
	//shaderManager->setActiveShader("testShader");
	//
	//camera
	//cam = new Camera();
	////
}

void BufferManager::clearBuffers()
{
	this->vertexes.clear();
	this->indices.clear();
	ElementBufferObjects.clear();
	VertexArrayObjects.clear();

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
	//VAO
	//GLuint VertexArrayObject;
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);
	//VBO
	//GLuint VertexBufferObject;
	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	//
	//GLuint ElementBufferObject;
	glGenBuffers(1, &ElementBufferObject);	

	//VBO bind & buffer data
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()* (GLuint)11 * sizeof(GLfloat),
		&vertices[0].Position.x, GL_DYNAMIC_DRAW);

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

	//EBO bind & buffer data
	glGenBuffers(1, &ElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
		&indices[0], GL_DYNAMIC_DRAW);

	VertexArrayObjects.push_back(VertexArrayObject);
	ElementBufferObjects.push_back(ElementBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
		glDrawElements(GL_TRIANGLES, indices[elementN].size(), GL_UNSIGNED_INT, 0);

		//glDrawElements(GL_TRIANGLES, this->indices[elementN].size(), GL_UNSIGNED_INT, 0);
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
	//
	//glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObject);
	//glBufferData(GL_ARRAY_BUFFER, this->objVertexes.size()* sizeof(Vertex),
	//	&this->objVertexes[0], GL_DYNAMIC_DRAW);
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBufferObject);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->objVertexes.size() * sizeof(GLuint),
	//	&this->objVertexes[0], GL_DYNAMIC_DRAW);
	//
	////Vertex Positions
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)0);
	//
	////Vertex Normals
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)offsetof(Vertex, Normal));
	//
	////Vertex Texture Coords
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)offsetof(Vertex, TexCoords));
	//
	////Vertex Color
	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)offsetof(Vertex, Color));
	//
	//VertexArrayObjects.push_back(newVAO);
	//
	//glBindVertexArray(0);
}
