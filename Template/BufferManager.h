#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <GL/glew.h>
#include <vector>
#include <iostream>

/*
Data structure
GLfloat position [x, y, z]
GLfloats color [r, g, b, a]
GLfloats texture coords [x, y]
*/
struct BufferData
{
	GLfloat Position[3];
	GLfloat Color[4];
	GLfloat TextCoord[2];
};

class BufferManager
{
public:
	BufferManager();
	~BufferManager();

	void addVertexData(GLfloat *data, GLsizei size);
	void addIndexData(GLfloat *data, GLsizei *size);

	void bindBuffer();
	void unbindBuffer();

	void initBuffers();
	void drawBuffer(std::vector<GLuint> buffer);
	
	//temporary init for shaders
	void initShaders();
	
protected:
private:
	std::vector<GLuint> vertexBuffer;
	std::vector<GLuint> indexBuffer;

	GLuint vertexbufId;
	GLuint indexbufID;

	// temporary shader
	GLuint vertexShader;
	GLuint fragmentShader;
	GLchar infoLog[512];
	GLuint shaderProgram;
	
};


#endif