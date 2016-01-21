#include "BufferManager.h"

BufferManager::BufferManager()
{

}

BufferManager::~BufferManager()
{
	if (bufId != 0)
	{
		glDeleteBuffers(1, &bufId);
	}

	
}

void BufferManager::bindBuffer()
{

}

void BufferManager::addVertexData(GLfloat data)
{
	GLuint bufId = 0;
	glGenBuffers(1, &bufId);
	glBindBuffer(GL_ARRAY_BUFFER, bufId);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(GLfloat),
		&vertexBuffer[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferManager::addIndexData(GLfloat data)
{
	GLuint bufId = 1;
	glGenBuffers(1, &bufId);
	glBindBuffer(GL_ARRAY_BUFFER, bufId);
	glBufferData(GL_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLfloat),
		&indexBuffer[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}