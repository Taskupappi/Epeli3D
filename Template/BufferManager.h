#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <GL/glew.h>
#include <ctime>
#include <vector>
#include <iostream>

#include <sstream>  

#include <glm\glm.hpp>
#include "ShaderManager.h"



//includes for the testBench
#include "amp.h"
#include "TempShader.h"
#include "Camera.h"


//
#include <ctime>
#include <glm\gtc\type_ptr.hpp>


//TO DO:
//Make shaders work properly with the buffer manager
//Clean up the unnecessary lines of code
//Add more commenting

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

	//possibly unnecessary files
	void addVertexData(GLfloat *data, GLsizei size);
	void addIndexData(GLuint *data, GLuint *size);

	void bindBuffer();
	void unbindBuffer();
	std::vector<GLuint> getBuffer(std::string bufferName);

	//called in the constructor
	void initBuffers();
	//temporary init for shaders
	void initShaders();	
	//add data to the buffers
	void addBufferData(std::vector<BufferVertex> vertices, std::vector<GLuint> indices, std::vector<BufferTexture> textures);
	//come here from the "addBufferData"
	void addBuffer();
	//RenderBuffers
	void drawBuffer(Shader shader);	

	//TestBench for the buffer
	void testBuffer();
	void initTest();
	void testBox();
	Shader getShader();
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	//cam
	Camera *cam;
	GLuint matrixID;
	glm::mat4 MVP;
	//


	//Buffer Data Vectors
	std::vector<BufferVertex> vertexBuffer;
	std::vector<GLuint> indicesBuffer;
	std::vector<BufferTexture> textures;

protected:

private:

	GLuint VertexArrayObject, VertexBufferObject, ElementBufferObject;

	//delete these?
	GLuint vertexbufId;
	GLuint indexbufID;

	// temporary shader
	GLuint vertexShader;
	GLuint fragmentShader;
	GLchar infoLog[512];
	GLuint shaderProgram;
	float tempColor = 0;
	Shader testShader;

	//testbench values
	int pos = 0;	
};


#endif