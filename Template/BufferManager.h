#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <GL/glew.h>
#include <vector>

class BufferManager
{
public:
	BufferManager();
	~BufferManager();

	void addVertexData(GLfloat data);
	void addIndexData(GLfloat data);

	void bindBuffer();
	void unbindBuffer();

	
protected:
private:
	std::vector<GLuint> vertexBuffer;
	std::vector<GLuint> indexBuffer;

	GLuint bufId;
};


#endif