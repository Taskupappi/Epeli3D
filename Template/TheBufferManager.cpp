#include "TheBufferManager.h"

TheBufferManager::TheBufferManager()
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
	initBuffers();
}

void TheBufferManager::clearBuffers()
{
	this->vertexes.clear();
	this->indices.clear();
	ElementBufferObjects.clear();
	VertexArrayObjects.clear();

}

TheBufferManager::~TheBufferManager()
{
	if (vertexbufID != 0)
	{
		glDeleteBuffers(1, &vertexbufID);
	}

	if (indexbufID != 0)
	{
		glDeleteBuffers(1, &indexbufID);
	}
}

void TheBufferManager::bindBuffer()
{
	/*if (vertexBuffer.size() != 0)
	{

	}*/
}
void TheBufferManager::initBuffers()
{
	//VAO
	//GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	//VBO
	//GLuint VertexBufferObject;
	glGenBuffers(1, &bigAssBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bigAssBuffer);
	//
	//GLuint ElementBufferObject;
	//glGenBuffers(1, &ElementBufferObject);

	//VBO bind & buffer data
	glBindBuffer(GL_ARRAY_BUFFER, bigAssBuffer);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size()* (GLuint)11 * sizeof(GLfloat),
	//	&vertices[0].Position.x, GL_DYNAMIC_DRAW);

	//Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (GLuint)12 * sizeof(GLfloat),
		(GLvoid*)0);

	//float size = sizeof(Vertex);
	//float size2 = (GLuint)11 * sizeof(GLfloat);

	//Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)(3 * sizeof(GLfloat)));

	//Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)(6 * sizeof(GLfloat)));

	//Vertex Color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)(8 * sizeof(GLfloat)));

	//EBO bind & buffer data
	//glGenBuffers(1, &ElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bigAssBuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
	//	&indices[0], GL_DYNAMIC_DRAW);

	//VertexArrayObjects.push_back(vertexArrayObject);
	//ElementBufferObjects.push_back(ElementBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TheBufferManager::bindBuffers(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{

	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, bigAssBuffer);
	//glBufferData(GL_ARRAY_BUFFER, );


	

















	//calculate the size of all vertexes in vertexVector
	GLsizei amountOfVertexes = 0;
	vertexVecIter = vertexes.begin();	

	for (vertexVecIter; vertexVecIter != vertexes.end(); vertexVecIter++)
	{
		amountOfVertexes += (*vertexVecIter).size();
	}


	//VAO
	//GLuint vertexArrayObject;
	//glGenVertexArrays(1, &vertexArrayObject);

	//VBO
	//GLuint VertexBufferObject;
	//glGenBuffers(1, &VertexBufferObject);
	//glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	//
	//GLuint ElementBufferObject;
	//glGenBuffers(1, &ElementBufferObject);	

	//VBO bind & buffer data
	glBindBuffer(GL_ARRAY_BUFFER, bigAssBuffer);
	glBufferData(GL_ARRAY_BUFFER, amountOfVertexes* (GLuint)12 * sizeof(GLfloat),
		&vertexes[0][0].Position.x, GL_DYNAMIC_DRAW);

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

	//EBO bind & buffer data
	//glGenBuffers(1, &ElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bigAssBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
		&indices[0], GL_DYNAMIC_DRAW);

	VertexArrayObjects.push_back(vertexArrayObject);
	//ElementBufferObjects.push_back(bigAssBuffer);

	//why would this be done when the game is on anyway?
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}

void TheBufferManager::addBufferData(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
	std::vector<Vertex> objVertexes;
	std::vector<GLuint> objIndices;

	objVertexes.insert(objVertexes.end(), vertices.begin(), vertices.end());
	objIndices.insert(objIndices.end(), indices.begin(), indices.end());

	this->vertexes.push_back(objVertexes);
	this->indices.push_back(objIndices);

	//bindBuffers(vertices, indices);
}

void TheBufferManager::drawBuffer(Shader* shader)
{
	int elementN = 0;
	VAOIter = VertexArrayObjects.begin();
	EBOIter = ElementBufferObjects.begin();


	std::vector<std::vector<GLuint>>::iterator IndexIter = indices.begin();

	glBindVertexArray(vertexArrayObject);



	/*/for (VAOIter; VAOIter != VertexArrayObjects.end(); VAOIter++)
	//{


	//	GLsizei IndicesSize = 0;
	//	for (IndexIter; IndexIter != indices.end(); IndexIter++)
	//	{
	//		IndicesSize += (*IndexIter).size();
	//	}

	//	IndexIter = indices.begin();

	//	elementN = std::distance(VertexArrayObjects.begin(), VAOIter);
	//	glBindVertexArray((*VAOIter));
	//	glDrawElements(GL_TRIANGLES, IndicesSize, GL_UNSIGNED_INT, (&EBOIter[0]));

	//	//glDrawArrays(GL_TRIANGLES, 0, IndicesSize);
	//	//glDrawElements(GL_TRIANGLES, this->indices[elementN].size(), GL_UNSIGNED_INT, 0);

	//	EBOIter++;
	//	glBindVertexArray(0);

	/}*/
}

void TheBufferManager::sendDataToOpenGL()
{

	//init stuff needed
	std::vector<Vertex> allVertexes;
	std::vector<GLuint> allIndices;
	int counter = 0;

	//Gather all vertexData into one vector
	for (vertexVecIter = vertexes.begin(); vertexVecIter != vertexes.end(); vertexVecIter++)
	{
		for (vertexIter = (*vertexVecIter).begin(); vertexIter != (*vertexVecIter).end(); vertexIter++)
		{
			allVertexes.push_back((*vertexVecIter)[counter]);
			counter++;
		}
		counter = 0;	
	}

	//gather all indices into one vector
	for (iteVecIndices = indices.begin(); iteVecIndices != indices.end(); iteVecIndices++)
	{
		for (iteIndices = (*iteVecIndices).begin(); iteIndices != (*iteVecIndices).end(); iteIndices++)
		{
			allIndices.push_back((*iteVecIndices)[counter]);
			counter++;
		}
		counter = 0;
	}


	//bind the VAO object and create a huge ass buffer
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, bigAssBuffer);
	glBufferData(GL_ARRAY_BUFFER, allVertexes.size() * (GLuint)12 * sizeof(GLfloat) + allIndices.size() * sizeof(GLuint), 0, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, bigAssBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bigAssBuffer);


	//this is just in case to prevent malfunctioning
	counter = 0;

	//this offset is for the for loop below.
	//keeps track of the offset for glBufferSubData.
	GLsizeiptr currentOffset = 0;

	//We iterate throught Vector of Vector of Vertices and do the same with idndices.
	//Idea here is to set all SubData for OpenGL in the right places with the right offsets 'n stuff.
	for (vertexVecIter = vertexes.begin(); vertexVecIter != vertexes.end(); vertexVecIter++)
	{
		//keep indices in the same part of  vector, filled with meshes as the vertexes are
		iteVecIndices = indices.begin();

		//we enter into each element held inside the vertexVecIterator.
		//vertexVecIterator points to the vectors that hold meshes.
		//vertexIter points to the actual meshes.
		for (vertexIter = (*vertexVecIter).begin(); vertexIter != (*vertexVecIter).end(); vertexIter++)
		{
			//keep indices in the same part of a mesh as the vertexes are
			iteIndices = (*iteVecIndices).begin();

			//add vertex data to the buffer
			glBufferSubData(GL_ARRAY_BUFFER, currentOffset, (*vertexVecIter).size() * (GLuint)12 * sizeof(GLfloat), (void*)(&vertexVecIter));
			currentOffset += (*vertexVecIter).size() * (GLuint)12 * sizeof(GLfloat);
			
			//add index data to the buffer
			glBufferSubData(GL_ARRAY_BUFFER, currentOffset, (*iteVecIndices).size() * sizeof(GLuint), (void*)(&iteVecIndices));
			currentOffset += (*iteVecIndices).size() * sizeof(GLuint);		


			//add counter to keep us in the right element
			counter++;

			//move indices at the same pace as vertexes
			iteIndices++;
		}//(vertexIter = (*vertexVecIter).begin(); vertexIter != (*vertexVecIter).end(); vertexIter++)

		//reset counters
		counter = 0;

		//move indices at the same pace as vertexes
		iteVecIndices;

	}//(vertexVecIter = vertexes.begin(); vertexVecIter != vertexes.end(); vertexVecIter++)

	
	glBindVertexArray(vertexArrayObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, bigAssBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bigAssBuffer);

}

////NOT FUNCTIONING/////
void TheBufferManager::setBufferData(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
	bindBuffers(vertices, indices);

	std::vector<Vertex> vt{};
	std::vector<GLuint> it{};

	//objVertexes.swap(vt);
	//objIndices.swap(it);

	//objVertexes.insert(objVertexes.begin(), vertices.begin(), vertices.end());
	//objIndices.insert(objIndices.begin(), indices.begin(), indices.end());

	this->addVertexArrayObject();
}

void TheBufferManager::addVertexArrayObject()
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
