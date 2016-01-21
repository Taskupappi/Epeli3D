#include "BufferManager.h"



void BufferManager::addVertexData(GLuint data)
{
	GLuint verBufId = 0;
	glGenBuffers(1, &verBufId);
	glBindBuffer(GL_ARRAY_BUFFER, verBufId);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(GLfloat),
		&vertexBuffer[0], GL_STATIC_DRAW);

	vertexBuffer.push_back(verBufId);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferManager::addIndexData(GLuint data)
{
	GLuint inBufId = 1;
	glGenBuffers(1, &inBufId);
	glBindBuffer(GL_ARRAY_BUFFER, inBufId);
	glBufferData(GL_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLfloat),
		&indexBuffer[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}