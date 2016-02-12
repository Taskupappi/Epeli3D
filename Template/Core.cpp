#include "Core.h"

using namespace core;
Engine* core::Engine::_instance = nullptr;
Engine::Engine() :_mainInit(false), _exit(false)
{
	//_resMngr = new ResourceManager();
	_scnMngr = new SceneManager();
	_input = new Input();
	//TO DO:
	//
	//shaderManager = nullptr;
	//bufferManager = nullptr;
	//textureManager = nullptr;
	//spriteManager = nullptr;
	//textManager = nullptr;
	//audioManager = nullptr;
}
Engine* Engine::UI()
{
	if (_instance == nullptr)
	{
		_instance = new Engine();
	}
	return _instance;
}
bool Engine::run()
{
	userInit();
	while(true)
	{
		processInput();
		gameLoop();
		if (_exit)
		{
			userUnInit();
			return _exit;
		}
	}
}
void Engine::userInit()
{ 
	if (_mainInit)
		return; 
	gameInit(); 
};
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
	int flags = MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG;
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG) != flags)
	{
		fprintf_s(stderr, "\nUnable to initialize SDL_audio: %s\n", SDL_GetError());
	}
	flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP;
	// SDL image init
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP) != flags)
	{
		fprintf_s(stderr, "\nUnable to initialize SDL_image: %s\n", SDL_GetError());
	}
	
	ResourceManager<TestiFoo>rm;
	ResourceMap<TestiFoo>mymap1;

	rm.initResourceManager("AssetDataBase");

	mymap1.initMapper("mapList1", &rm, true);

	mymap1.addElement("PNG_Image", "../data/Resource/Images/sample.png", 0);
	mymap1.addElement("JPEG_Image", "../data/Resource/Images/doge.jpeg", 0);
	mymap1.addElement("WAV_Audio", "../data/Resource/Audio/sample.wav", 0);

	mymap1.getElement("JPEG_Image");

	mymap1.removeElement("JPEG_Image");

	mymap1.dump();
	
	////GlewInit()
	//glewExperimental = GL_TRUE;

	//glewInit();

	//freetype init()
	//
	//Do we even want this here?
	//
}


void Engine::Uninit()
{
	Mix_CloseAudio();
	Mix_Quit();

	//SDL Uninit
	atexit(SDL_Quit);
}

void Engine::processInput()
{
	/*
	TODO: SDL Input handler here:
	SDL_MOUSEBUTTONDOWN
	SDL_MOUSEBUTTONUP
	SDL_MOUSEMOTION
	*/

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			_exit = true;
		}
		if (e.type == SDL_KEYUP)
		{
			_input->addReleasedKey(e.key.keysym.sym);
			SDL_Log("Key Up %s", SDL_GetKeyName(e.key.keysym.sym));
		}
		if (e.type == SDL_KEYDOWN)
		{
			SDL_Log("Key Down %s", SDL_GetKeyName(e.key.keysym.sym));
			//Not necessarily needed for pressed keys uses SDL_GetKeyboardState
			_input->addPressedKey(e.key.keysym.sym);
			if (e.key.keysym.sym == SDLK_ESCAPE)
				_exit = true;
		}
	}
}
