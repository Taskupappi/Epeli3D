#include "Core.h"

using namespace core;

Engine::Engine()
{



	//TO DO:
	//
	//shaderManager = nullptr;
	//bufferManager = nullptr;
	//textureManager = nullptr;
	//spriteManager = nullptr;
	//textManager = nullptr;
	//audioManager = nullptr;
}


Engine::~Engine()
{

}

void Engine::Init()
{

	
	//SDL Init()
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
	{
		fprintf_s(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());		
	}	

	// SDL audio init
	
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG))
	{
		fprintf_s(stderr, "\nUnable to initialize SDL_audio: %s\n", SDL_GetError());
	}
	
	// SDL image init
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP))
	{
		fprintf_s(stderr, "\nUnable to initialize SDL_image: %s\n", SDL_GetError());
	}
	
	//GlewInit()
	glewExperimental = GL_TRUE;

	glewInit();

	//freetype init()
	//
	//Do we even want this here?
	//
}


void Engine::Uninit()
{


	//SDL Uninit
	atexit(SDL_Quit);
	
}

