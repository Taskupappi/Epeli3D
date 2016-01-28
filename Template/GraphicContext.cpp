#include "GraphicContext.h"

GraphicContext::GraphicContext()
{
	window = nullptr;	

	window = SDL_CreateWindow(
		"Epeli3D",
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		x,
		y,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	//openGL context
	glcontext = SDL_GL_CreateContext(window);	

	//GlewInit()
	glewExperimental = GL_TRUE;
	glewInit();
}

GraphicContext::GraphicContext(int xRes, int yRes)
{
	x = xRes;
	y = yRes;
	GraphicContext::GraphicContext();
}

GraphicContext::~GraphicContext()
{	
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(glcontext);
}

void GraphicContext::setResolution(int xRes, int yRes)
{
//	SDL_SetWindowDisplayMode(window, );
}

void GraphicContext::swap()
{
	SDL_GL_SwapWindow(window);
}

void GraphicContext::clear()
{
	//clear the backbuffer and depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}