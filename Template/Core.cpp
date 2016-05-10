#include "Core.h"

using namespace core;
Engine* core::Engine::_instance = nullptr;
Engine::Engine() :_mainInit(false), _exit(false)
{
	createScreen(800.0f, 600.0f);
	//_resMngr = new ResourceManager();
	_scnMngr = new SceneManager();
	_input = new Input();
	_bufMngr = new BufferManager();
	_shdrMngr = new graphics::ShaderManager();
	//_sprtMngr = new graphics::SpriteManager(_bufMngr, nullptr);// _shdrMngr);
	_resMngr = new Resources("Resource", 0);
	_txtrMngr = new TextureManager(_resMngr);
	_sndMngr = new AudioManager(_resMngr);
	//_grapCtx = nullptr;
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
	delete _resMngr;
	//delete _sprtMngr;
	delete _bufMngr;
	delete _input;
	delete _scnMngr;
	//delete _shdrMngr;
}

Engine* Engine::UI()
{
	if (_instance == nullptr)
	{
		_instance = new Engine();
	}
	return _instance;
}

void Engine::Init()
{
	//SDL Init()
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
	{
		fprintf_s(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
	}

	// SDL audio init
	int flags = MIX_INIT_MP3 | MIX_INIT_MOD | MIX_INIT_OGG;
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		//This is so that the engine runs without soundevice
		//exit(2); 
	}
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_MOD | MIX_INIT_OGG) != flags)
	{
		fprintf_s(stderr, "\nUnable to initialize SDL_audio: %s\n", SDL_GetError());
	}
	flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP;
	// SDL image init
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP) != flags)
	{
		fprintf_s(stderr, "\nUnable to initialize SDL_image: %s\n", SDL_GetError());
	}
	// GLEW init
	glewInit();



	//createScreen(800, 600);
	//_shdrMngr->createShader("../data/shaders/VertexShaderTest.glvs", "../data/shaders/FragmentShaderTest.glfs", "testShader");
	//std::cout << "Model loading:" << std::endl;
	//Object3D object("../data/Resource/Models/boy.obj");
	//std::cout << ".obj loaded" << std::endl;
	//Object3D object2("../data/Resource/Models/boy.3ds");
	//std::cout << ".3ds loaded" << std::endl;
	//Object3D object3("../data/Resource/Models/boy.lwo");
	//std::cout << ".lwo loaded" << std::endl;
	//Object3D object4("../data/Resource/Models/Shark.dae");
	//std::cout << ".dae loaded" << std::endl;
	//Object3D object5("../data/Resource/Models/Shark.stl");
	//std::cout << ".stl loaded" << std::endl;
	//Object3D object6("../data/Resource/Models/smg_low.x");
	//std::cout << ".x   loaded" << std::endl;
	//Object3D object7("../data/Resource/Models/smg_low.ply"); //hiukan hidas
	//std::cout << ".ply loaded" << std::endl;
	//std::cout << "Model loading end." << std::endl;

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

bool Engine::run()
{
	userInit();
	while (true)
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

void Engine::createScreen(int ResX, int ResY)
{
	_grapCtx = new GraphicContext(ResX, ResY);
}

graphics::Sprite * core::Engine::createSprite(Texture * texture, glm::vec2 position, glm::vec2 size, int z, Color col)
{
	graphics::Sprite * sprt = nullptr;
	//TODO: uncomment once textures are done
	sprt = _sprtMngr->createSprite(glm::vec3(position.x, position.y, z), size, glm::vec2(size.x / 2, size.y / 2), col, texture, 1, 1);
	return sprt;
}

Texture * Engine::createTexture(std::string filepath)
{
	Texture *texture = _txtrMngr->createTexture(filepath);

	return texture;
}

Audio * Engine::createAudio(std::string filepath)
{
	Audio *audio = _sndMngr->createSound(filepath);

	return audio;
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
			if ((_input->isKeyPressed(SDLK_LALT)) && (e.key.keysym.sym == SDLK_F4))
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


//TestBench to try out modules
void Engine::testInit(Camera* cam, GLfloat screenWidth, GLfloat screenHeight)
{	
	_shdrMngr->createShader("../data/shaders/vertexKisse.glvs", "../data/shaders/fragmentKisse.glfs", "testShader");
	_shdrMngr->setActiveShader("testShader");

	//camera stuff
	cam->initDefault(_shdrMngr->getActiveShader());

	//Model loading
	Object3D * model = _resMngr->loadFile<Object3D>("../data/Resource/Models/cube.obj");

	std::vector<Vertex> v3D;
	std::vector<GLuint> indices3D;

	std::vector<Mesh>::iterator modelIter;
	std::vector<Vertex>::iterator vertexIter;
	std::vector<GLuint>::iterator indicesIter;

	std::vector<Mesh> mesh;
	mesh = model->getMeshVec();

	for (modelIter = model->getMeshVec().begin(); modelIter != model->getMeshVec().end(); modelIter++)
	{
		for (vertexIter = modelIter->vertices.begin(); vertexIter != modelIter->vertices.end(); vertexIter++)
		{
			v3D.push_back((*vertexIter));
		}

		for (indicesIter = modelIter->indices.begin(); indicesIter != modelIter->indices.end(); indicesIter++)
		{
			indices3D.push_back((*indicesIter));
		}
	}


	std::vector<Vertex>::iterator color;
	for (color = v3D.begin(); color != v3D.end(); color++)
	{
		//glm::rotate((*color).Position, 50.0f, (*color).Normal);
		//(*color).Position.z -= 145.5f;
		(*color).Color = glm::vec4(125, 125, 125, 1);
	}

	//_bufMngr->addBufferData(v3D, indices3D);
	
	//end of model loading
		
	//Model loading 2
	Object3D * model2 = _resMngr->loadFile<Object3D>("../data/Resource/Models/fucboi.obj");

	std::vector<Vertex> v3D2;
	std::vector<GLuint> indices3D2;

	std::vector<Mesh>::iterator modelIter2;
	std::vector<Vertex>::iterator vertexIter2;
	std::vector<GLuint>::iterator indicesIter2;

	std::vector<Mesh> mesh2;
	mesh2 = model2->getMeshVec();
	
	for (modelIter2 = model2->getMeshVec().begin(); modelIter2 != model2->getMeshVec().end(); modelIter2++)
	{
		for (vertexIter2 = modelIter2->vertices.begin(); vertexIter2 != modelIter2->vertices.end(); vertexIter2++)
		{
			v3D2.push_back((*vertexIter2));
		}

		for (indicesIter2 = modelIter2->indices.begin(); indicesIter2 != modelIter2->indices.end(); indicesIter2++)
		{
			indices3D2.push_back((*indicesIter2));
		}
	}


	//std::vector<Vertex>::iterator color;
	for (color = v3D2.begin(); color != v3D2.end(); color++)
	{
		//glm::rotate((*color).Position, 50.0f, (*color).Normal);
		(*color).Position += glm::vec3(0.5f);
		(*color).Position.x += 4.5f;
		(*color).Color = glm::vec4(0, 125, 26, 0.2);
		//(*color).Color = glm::vec4(0, 125, 26, 1);
	}
	_bufMngr->addBufferData(v3D2, indices3D2);
	_bufMngr->addBufferData(v3D, indices3D);
	

		////lighting
		////GLuint lighting;
		////newVAO(lighting);	
}

void Engine::testUpdate(Camera* cam, float deltaTime, const glm::vec2 mousePosition, const char* input)
{
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	//glBindVertexArray(VAOs[0]);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, (void*)0);
	//glBindVertexArray(0);

	_shdrMngr->useActiveShader();
	GLfloat radius = 10.0f;
	GLfloat camX = sin(deltaTime) * radius;
	GLfloat camZ = cos(deltaTime) * radius;

	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	cam->mouseUpdate(mousePosition);
	cam->move(input, deltaTime);
	//cam->setViewMatrix(view);

	//glRotatef(deltaTime * 15, 1.0f, 1.0f, 0.0f);

	cam->passMatricesToShader(_shdrMngr->getActiveShader());
	_bufMngr->drawBuffer(_shdrMngr->getActiveShader());

	_grapCtx->swap();
	glPopMatrix();

	//cam->printDetails();
	//cam->printMatrices();
}