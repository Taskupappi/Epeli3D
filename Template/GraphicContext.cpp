#include "GraphicContext.h"

GraphicContext::GraphicContext()
{
	window = nullptr;	

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	window = SDL_CreateWindow(
		"Epeli3D",
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		x,
		y,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	//openGL context
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	glcontext = SDL_GL_CreateContext(window);	

	

	//multisampling?
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	//glEnable(GL_MULTISAMPLE);

	//GlewInit()
	glewExperimental = GL_TRUE;
	glewInit();



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_2D);
	//glShadeModel(GL_SMOOTH);
}

GraphicContext::GraphicContext(int xRes, int yRes)
{
	x = xRes;
	y = yRes;
	
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_2D);
	//glShadeModel(GL_SMOOTH);
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