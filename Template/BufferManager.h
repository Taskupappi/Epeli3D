#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <GL/glew.h>
#include <vector>
#include <iostream>

#include <sstream>  

#include <glm\glm.hpp>
#include "ShaderManager.h"

//tempShadertesting
#include "TempShader.h"

//includes for the testBench
#include "amp.h"
#include <ctime>




/*
Data structure
GLfloat position [x, y, z]
GLfloats color [r, g, b, a]
GLfloats texture coords [x, y]
*/


struct BufferVertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Color;
};

struct BufferTexture
{
	GLuint id;
	std::string type;
};

class BufferManager
{
public:
	BufferManager();
	~BufferManager();

	void addVertexData(GLfloat *data, GLsizei size);
	void addIndexData(GLuint *data, GLuint *size);

	void bindBuffer();
	void unbindBuffer();
	std::vector<GLuint> getBuffer(std::string bufferName);


	//called in the constructor
	void initBuffers();
	//temporary init for shaders
	void initShaders();	
	//Add data to the buffers
	void addBufferData(std::vector<BufferVertex> vertices, std::vector<GLuint> indices, std::vector<BufferTexture> textures);
	//here from the "addBufferData"
	void addBuffer();
	//RenderBuffers
	void drawBuffer(Shader shader);	
	//TestBench for the buffer
	void testBuffer();

	//buffer Data
	std::vector<BufferVertex> vertexBuffer;
	std::vector<GLuint> indicesBuffer;
	std::vector<BufferTexture> textures;
protected:
private:

	GLuint VertexArrayObject, VertexBufferObject, ElementBufferObject;


	GLuint vertexbufId;
	GLuint indexbufID;

	// temporary shader
	GLuint vertexShader;
	GLuint fragmentShader;
	GLchar infoLog[512];
	GLuint shaderProgram;
	float tempColor = 0;
	
};


#endif