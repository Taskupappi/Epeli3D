#include "Core.h"

using namespace core;
Engine* core::Engine::_instance = nullptr;
Engine::Engine() :_mainInit(false), _exit(false)
{
	//_resMngr = new ResourceManager();
	_scnMngr = new SceneManager();
	_input = new Input();
	_bufMngr = new BufferManager();
	_sprtMngr = new graphics::SpriteManager(_bufMngr);
	//_shdrMngr = new graphics::ShaderManager();
	_resMngr = new Resources("Resource", 0);
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
	delete _resMngr;
	delete _sprtMngr;
	delete _bufMngr;
	delete _input;
	delete _scnMngr;
	//delete _shdrMngr;
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
		//This is so that the engine runs without soundevice
		//exit(2); 
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
	
	Resources *res = _resMngr;
	// TODO: TextureManager
	Texture * tex = res->loadFile<Texture>("../data/Resource/Images/sample.png");
	// TODO: AudioManager hoitamaan toiston kontrolleja yms
	Audio * audio = res->loadFile<Audio>("../data/Resource/Audio/samppeli.mp3");
	Texture * tex2 = res->loadFile<Texture>("../data/Resource/Images/sample.png");
	Text * txt = res->loadFile<Text>("../data/Shaders/FragmentShaderTest.glfs");
	Audio * audio2 = res->loadFile<Audio>("../data/Resource/Audio/samppeli.mp3");
	Text * txt2 = res->loadFile<Text>("../data/Shaders/FragmentShaderTest.glfs");

	std::cout << "Model loading:" << std::endl;
	Object3D object("../data/Resource/Models/boy.obj");
	std::cout << ".obj loaded" << std::endl;
	Object3D object2("../data/Resource/Models/boy.3ds");
	std::cout << ".3ds loaded" << std::endl;
	Object3D object3("../data/Resource/Models/boy.lwo");
	std::cout << ".lwo loaded" << std::endl; 
	Object3D object4("../data/Resource/Models/Shark.dae");
	std::cout << ".dae loaded" << std::endl; 
	Object3D object5("../data/Resource/Models/Shark.stl");
	std::cout << ".stl loaded" << std::endl; 
	Object3D object6("../data/Resource/Models/smg_low.x");
	std::cout << ".x   loaded" << std::endl; 
	Object3D object7("../data/Resource/Models/smg_low.ply"); //hiukan hidas
	std::cout << ".ply loaded" << std::endl;
	std::cout << "Model loading end." << std::endl;

	//Mix_PlayMusic(audio, 1);

	//mymap1.getElement("JPEG_Image");

	//mymap1.removeElement("JPEG_Image");

	//mymap1.dump();

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
	delete this;
}
graphics::Sprite * Engine::createSprite(glm::vec2 position, glm::vec2 size, int z, Color col, Texture * tex)
{
	graphics::Sprite * sprt = nullptr;
	//TODO: uncomment once textures are done
	//sprt = _sprtMngr->createSprite(glm::vec3(position.x, position.y, z), size, glm::vec2(size.x / 2, size.y / 2), tex, 1, 1);
	return sprt;
}
void Engine::processInput()
{
	//SDL Input handler here
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
			//if (e.key.keysym.sym == SDLK_ESCAPE)
			//	_exit = true;
			//ALT + F4 pressed
			if((_input->isKeyPressed(SDLK_LALT)) && (e.key.keysym.sym == SDLK_F4))
				_exit = true;

		}
		if (e.type == SDL_MOUSEMOTION)
		{
			_input->_mouse.setMouseMovement(glm::vec2(e.motion.x, e.motion.y), glm::vec2(e.motion.xrel, e.motion.yrel));
		}
		if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		{
			Mouse::mBstate s = Mouse::unknown;
			if (e.button.state == SDL_PRESSED)
				s = Mouse::pressed;
			else
				s = Mouse::released;
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				_input->_mouse.setMouseBState(Mouse::left, s);
				break;
			case SDL_BUTTON_RIGHT:
				_input->_mouse.setMouseBState(Mouse::right, s);
				break;
			case SDL_BUTTON_MIDDLE:
				_input->_mouse.setMouseBState(Mouse::middle, s);
				break;
			}
		}
	}
}
