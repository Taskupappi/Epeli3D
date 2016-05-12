#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H
#include <GL/glew.h>
//#include <GL/glew.h>
#include <vector>
//#include <glm\gtc\type_ptr.hpp>

#include <glm\glm.hpp>
#include "Vertex.h"
#include "Shader.h"

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
	void updateData();
	void bindBuffers();
	void initBuffers();
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

	//BufferData for multiple objects
	std::vector<std::vector<Vertex>> vertexes;
	std::vector<std::vector<GLuint>>indices;

	std::vector<Vertex> allVertexes;
	std::vector<GLuint> allIndices;
	std::vector<GLuint> offsetVertices;
	std::vector<GLuint> offsetIndices;

	std::vector<std::vector<GLuint>>::iterator iteVecIndices;
	std::vector<GLuint>::iterator iteIndices;

	std::vector<std::vector<Vertex>>::iterator vertexVecIter;
	std::vector<Vertex>::iterator vertexIter;

	//Buffer Data Vectors for object
	//std::vector<Vertex> objVertexes;
	//std::vector<GLuint> objIndices;
	std::vector<Vertex>::iterator* objVerIter;
	std::vector<GLuint>::iterator* objIndIter;	
	

	std::vector<GLuint> ElementBufferObjects;
	std::vector<GLuint> VertexArrayObjects;
	std::vector<GLuint>::iterator VAOIter;
	std::vector<GLuint>::iterator EBOIter;
	/////
protected:

private:



	GLuint
		VertexArrayObject,
		VertexBufferObject,
		ElementBufferObject;
		//NormalBufferObject;

	//Struct 
	struct Vertex vertex;

	//delete these?
	GLuint vertexbufId;
	GLuint indexbufID;
};
#endif