#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <GL/glew.h>
#include <vector>

class BufferManager
{
public:
	void addVertexData(GLuint data);
	void addIndexData(GLuint data);
protected:
private:
	std::vector<GLuint> vertexBuffer;
	std::vector<GLuint> indexBuffer;
};


#endif