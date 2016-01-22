#include "GraphicContext.h"

GraphicContext::GraphicContext()
{
	window = SDL_CreateWindow(
		"Epeli3D",
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
}

GraphicContext::GraphicContext(int xRes, int yRes)
{
	window = SDL_CreateWindow(
		"Epeli3D",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		xRes,
		yRes,
		SDL_WINDOW_OPENGL);
}

GraphicContext::~GraphicContext()
{
	SDL_DestroyWindow(window);
}

void GraphicContext::Init()
{
	
}

void GraphicContext::setResolution(int xRes, int yRes)
{
//	SDL_SetWindowDisplayMode(window, );
}