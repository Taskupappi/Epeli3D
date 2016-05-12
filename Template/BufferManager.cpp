#include "BufferManager.h"

BufferManager::BufferManager()
{
	initBuffers();
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
}

void BufferManager::initBuffers()
{
	//VAO
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	//VBO
	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);

	//GLuint ElementBufferObject;
	glGenBuffers(1, &ElementBufferObject);

	//VBO bind & buffer data
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);

	//Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (GLuint)12 * sizeof(GLfloat), (GLvoid*)0);

	//Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)( 3*sizeof(GLfloat)));

	//Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)(6 * sizeof(GLfloat)));

	//Vertex Color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)(8 * sizeof(GLfloat)));

	//EBO bind & buffer data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BufferManager::addBufferData(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{		 
	std::vector<Vertex> objVertexes;
	std::vector<GLuint> objIndices;

	objVertexes.insert(objVertexes.end(), vertices.begin(), vertices.end());
	objIndices.insert(objIndices.end(), indices.begin(), indices.end());

	this->vertexes.push_back(objVertexes);
	this->indices.push_back(objIndices);
}

void BufferManager::updateData()
{
	int counter = 0;
	allVertexes.clear();
	allIndices.clear();
	int offset = 0;

	//Gather all vertexData into one vector
	for (vertexVecIter = vertexes.begin(); vertexVecIter != vertexes.end(); vertexVecIter++)
	{
		offsetVertices.push_back((*vertexVecIter).size());

		for (vertexIter = (*vertexVecIter).begin(); vertexIter != (*vertexVecIter).end(); vertexIter++)
		{
			allVertexes.push_back((*vertexVecIter)[counter]);
			counter++;
		}
		counter = 0;
	}

	//gather all indices into one vector
	for (int i = 0; i < indices.size(); i++)
	{
		for (int y = 0; y < indices[i].size(); y++)
		{			
			allIndices.push_back(indices[i][y] + offset);			
		}	
		offset += indices[i].size();
	}
}


void BufferManager::bindBuffers()
{
	updateData();

	//VAO
	glBindVertexArray(VertexArrayObject);

	//VBO bind & buffer data
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, allVertexes.size() * (GLuint)12 * sizeof(GLfloat), &allVertexes[0], GL_STATIC_DRAW);
		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, allIndices.size() *(GLuint)1 * sizeof(GLuint), &allIndices[0], GL_DYNAMIC_DRAW);
}

void BufferManager::drawBuffer(Shader* shader)
{
	bindBuffers();

	glDrawElements(GL_TRIANGLES, allIndices.size(), GL_UNSIGNED_INT, (void*)allIndices[0]);//(void*)allIndices[0]);
	//glDrawArrays(GL_TRIANGLES, allIndices[0], allIndices.size());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

////NOT FUNCTIONING/////
void BufferManager::setBufferData(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
	bindBuffers();

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
