#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <GL/glew.h>
#include <ctime>
#include <vector>
#include <iostream>
#include <array>
#include <sstream>  

#include <ctime>
#include <glm\gtc\type_ptr.hpp>

#include <glm\glm.hpp>
#include "Vertex.h"

//includes for the testBench
#include "amp.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Input.h"
#include <glm/gtx/rotate_vector.hpp>
////3d object loading
#include "Object3D.h"
#include <math.h>
#include <cstddef>

#include "Input.h"
//


//TO DO:
//Make shaders work properly with the buffer manager
//Clean up the unnecessary lines of code
//Add more commenting

//TESTBENCH STUFF
enum SHADERSELECTOR
{
	TEST = 1,
	LAMP = 2
};

namespace core
{
	class Engine;
}

class BufferManager
{
public:
	BufferManager();
	~BufferManager();

	//called in the constructor
	void initBuffers(std::vector<Vertex> vertices, std::vector<GLuint> indices);

	void addVertexData(GLfloat *data, GLsizei size);
	void addIndexData(GLuint *data, GLuint *size);

	void bindBuffer();
	void unbindBuffer();
	std::vector<GLuint> getBuffer(std::string bufferName);	

	//add data to the buffers in following format
	//glm::vec3 Position, glm::vec3 Normal, glm::vec2 TexCoords, glm::vec3 Color
	void addBufferData(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	//come here from the "addBufferData"
	void addVertexArrayObject();
	
	void setBufferData(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	void clearBuffers();

	//RenderBuffers
	void drawBuffer(Shader *shader);
	void drawElement(Shader* shader);

	//binds a new Vertex Array Object for use
	void newVAO(const GLuint vao);	

	//TESTBENCH STUFF
	//Cam
	Camera* getCamera();
	Camera *cam;
	GLuint matrixID;
	glm::mat4 MVP;

	GLfloat camX = 2;
	GLfloat camY = 0;
	GLfloat camZ = 15;

	//lightPos 
	glm::vec3 lightPos;
	
	//Shader manager
	ShaderManager *shaderManager;

	//TestBench for the buffer
	void drawTestBuffer();
	void initTest();
	void testBox();
	void testBoxUpdate();
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	float rotation = 0;

	//3DModel loading
	Object3D model3D;
	
	//this should be moved to the game object
	void calculateModelMatrix();
	////

	//BufferData for multiple objects
	std::vector<std::vector<Vertex>> vertexes;
	std::vector<std::vector<GLuint>>indices;

	//Buffer Data Vectors for object
	//std::vector<Vertex> objVertexes;
	//std::vector<GLuint> objIndices;
	std::vector<Vertex>::iterator* objVerIter;
	std::vector<GLuint>::iterator objIndIter;

	
	
	std::vector<GLuint> VertexArrayObjects;
	std::vector<GLuint>::iterator VAOIter;
	/////
protected:

private:

	GLuint
		//VertexArrayObject,
		VertexBufferObject, 
		ElementBufferObject,
		NormalBufferObject;

	//Struct 
	struct Vertex vertex;

	//delete these?
	GLuint vertexbufId;
	GLuint indexbufID;

	// temporary shader
	float tempColor = 0;
	bool rewind;
	GLfloat angle;
	//testbench values
	int pos = 0;
};
#endif