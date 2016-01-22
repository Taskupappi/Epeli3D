#ifndef GRAPHICALCONTEXT_H
#define GRAPHICALCONTEXT_H

#include "SDL.h"

class GraphicContext
{
public:
	GraphicContext();
	GraphicContext(int xRes, int yRes);
	~GraphicContext();
	void setResolution(int xRes, int yRes);
	void Init();
private:
	int screenWidth, screenHeight;
	SDL_Window *window;
};



#endif
