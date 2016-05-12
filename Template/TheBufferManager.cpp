#include "TheBufferManager.h"

TheBufferManager::TheBufferManager()
{	
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &elementBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);
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
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//VBO
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	//Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (GLuint)12 * sizeof(GLfloat), (GLvoid*)0);

	//Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));

	//Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));

	//Vertex Color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

	//EBO bind & buffer data
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TheBufferManager::bindBuffers(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{

	glBindVertexArray(vertexArrayObject);

	//calculate the size of all vertexes in vertexVector
	GLsizei amountOfVertexes = 0;
	vertexVecIter = vertexes.begin();	

	for (vertexVecIter; vertexVecIter != vertexes.end(); vertexVecIter++)
	{
		amountOfVertexes += (*vertexVecIter).size();
	}

	//VBO bind & buffer data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, amountOfVertexes* (GLuint)12 * sizeof(GLfloat), &vertexes[0][0].Position.x, GL_DYNAMIC_DRAW);

	////Vertex Positions
	//EBO bind & buffer data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_DYNAMIC_DRAW);

	VertexArrayObjects.push_back(vertexArrayObject);
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
	shader->use();
	glDrawElements(GL_TRIANGLES, allIndices.size(), GL_UNSIGNED_INT, (void*)0);



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
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, allVertexes.size() * (GLuint)12 * sizeof(GLfloat) + allIndices.size() * sizeof(GLuint), 0, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);


	//glBindBuffer(GL_ARRAY_BUFFER, bigAssBuffer);
	//glBufferData(GL_ARRAY_BUFFER, amountOfVertexes* (GLuint)12 * sizeof(GLfloat), &vertexes[0][0].Position.x, GL_DYNAMIC_DRAW);

	////Vertex Positions
	//EBO bind & buffer data
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bigAssBuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_DYNAMIC_DRAW);























	//this is just in case to prevent malfunctioning
	counter = 0;

	//this offset is for the for loop below.
	//keeps track of the offset for glBufferSubData.
	GLsizeiptr currentOffset = 0;

	iteVecIndices = indices.begin();

	//We iterate throught Vector of Vector of Vertices and do the same with idndices.
	//Idea here is to set all SubData for OpenGL in the right places with the right offsets 'n stuff.
	for (vertexVecIter = vertexes.begin(); vertexVecIter != vertexes.end(); vertexVecIter++)
	{
		//keep indices in the same part of  vector, filled with meshes as the vertexes are
		

		//we enter into each element held inside the vertexVecIterator.
		//vertexVecIterator points to the vectors that hold meshes.
		//vertexIter points to the actual meshes.
		/*for (vertexIter = (*vertexVecIter).begin(); vertexIter != (*vertexVecIter).end(); vertexIter++)
		{*/
			//keep indices in the same part of a mesh as the vertexes are
			//iteIndices = (*iteVecIndices).begin();

			//add vertex data to the buffer
			glBufferSubData(GL_ARRAY_BUFFER, currentOffset, (*vertexVecIter).size() * (GLuint)12 * sizeof(GLfloat), (void*)(&vertexVecIter[0]));
			currentOffset += (*vertexVecIter).size() * (GLuint)12 * sizeof(GLfloat);
			
			//add index data to the buffer
			glBufferSubData(GL_ARRAY_BUFFER, currentOffset, (*iteVecIndices).size() * sizeof(GLuint), (void*)(&iteVecIndices[counter]));
			currentOffset += (*iteVecIndices).size() * sizeof(GLuint);

			//add counter to keep us in the right element
			//counter++;

			//move indices at the same pace as vertexes
			//iteIndices++;
		//}//(vertexIter = (*vertexVecIter).begin(); vertexIter != (*vertexVecIter).end(); vertexIter++)

		//reset counters
		//counter++;

		//move indices at the same pace as vertexes
		iteVecIndices++;

	}//(vertexVecIter = vertexes.begin(); vertexVecIter != vertexes.end(); vertexVecIter++)

	
	glBindVertexArray(vertexArrayObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

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

















/*

GLsizeiptr currentOffset = 0;
int counter = 0;

for (unsigned i = 0; i < vertexes.size(); i++)
{
int indicesCounter = i;


//add vertex data to the buffer
glBufferSubData(GL_ARRAY_BUFFER, currentOffset, vertexes.size() * (GLuint)12 * sizeof(GLfloat), &vertexes[i][y]);
//offset is the size of a vertex vector
currentOffset += (GLuint)12 * sizeof(GLfloat);

//add index data to the buffer
glBufferSubData(GL_ARRAY_BUFFER, currentOffset, (*iteVecIndices).size() * sizeof(GLuint), (void*)(&iteVecIndices[counter]));
currentOffset += (GLuint)1 * sizeof(GLuint);



for (unsigned y = 0; y < vertexes[i].size(); y++)
{

}


}

*/