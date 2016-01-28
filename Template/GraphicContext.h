#ifndef GRAPHICALCONTEXT_H
#define GRAPHICALCONTEXT_H

#include "SDL.h"
#include <SDL_opengl.h>

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

private:
	int screenWidth, screenHeight;

	SDL_Window *window;
	SDL_GLContext glcontext;

	int x = 800;
	int y = 600;


	
};



#endif
