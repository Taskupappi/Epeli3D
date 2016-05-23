#ifndef GRAPHICCONTEXT_H
#define GRAPHICCONTEXT_H

#define GLEW_STATIC
#include <GL\glew.h>
#include <gl\glew.h>

#include "SDL.h"
#include <SDL_opengl.h>
#include <GLFW\glfw3.h>
#include "Color.h"

class GraphicContext
{
public:
	GraphicContext();
	GraphicContext(int xRes, int yRes);
	~GraphicContext();

	//Not sure if this is needed really
	void setResolution(int xRes, int yRes);

	//swap graphical context
	void swap();
	//clear window
	void clear();
	void GraphicContext::clear(Color c)
	{
		glClearColor(c.getAsOGLVec().r,c.getAsOGLVec().g,c.getAsOGLVec().b,c.getAsOGLVec().a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	}
private:
	int screenWidth, screenHeight;

	SDL_Window *window;
	SDL_GLContext glcontext;

	int x = 800;
	int y = 600;


	
};



#endif
