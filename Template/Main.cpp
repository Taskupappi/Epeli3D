#include "Core.h"
#include "ResourceManager.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_GLContext glcontext;
core::Engine * eng = core::Engine::UI();
ResourceManager * resMngr;
Image * img;
//Called before engine closes
void userUnInit(){};
//Game initialization code here
void gameInit()
{
	resMngr = new ResourceManager();
	img = resMngr->loadResourceT<Image>("kuva.png");
	window = SDL_CreateWindow("Epeli3D", 10, 30, 640, 480,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	//glcontext = SDL_GL_CreateContext(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
}
//Game mainloop
void gameLoop()
{

	//glClearColor(0, 255, 255, 1);
	//glClear(GL_COLOR_BUFFER_BIT);
	SDL_Rect rects;
	rects.x = 320;
	rects.y = 200;
	rects.w = 80;
	rects.h = 80;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRects(renderer,&rects, 1);
	SDL_RenderPresent(renderer);
	//SDL_GL_SwapWindow(window);

}

int main(int argc, char** argv)
{
	eng->Init();
	eng->run();
	eng->Uninit();
	
	//SDL_Init(SDL_INIT_EVERYTHING);

	return 0;
}