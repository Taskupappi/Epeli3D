#include "Core.h"

using namespace core;
Engine* core::Engine::_instance = nullptr;
Engine::Engine() :_mainInit(false), _exit(false)
{
	//_resMngr = new ResourceManager();
	_scnMngr = new SceneManager();
	_input = new Input();
	_bufMngr = new BufferManager();
	_shdrMngr = new ShaderManager();
	//_sprtMngr = new graphics::SpriteManager(_bufMngr, nullptr);// _shdrMngr);
	_resMngr = new Resources("Resource", 0);
	_txtrMngr = new TextureManager(_resMngr);
	_grapCtx = nullptr;
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
	delete _sprtMngr;
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

	// TODO: fix this
	//ImageResource* imgData;
	//imgData = _txtrMngr->createTexture("../data/Resource/Images/sample.png");
	//Texture *texture = new Texture(0);
	//// sisälle filepath??? vai mitähä???
	//texture->bindTexture(imgData);

	Texture * texture = new Texture(_txtrMngr);
	texture->createTexture("../data/Resource/Images/sample.png");
	Texture * texture2 = new Texture(_txtrMngr);
	texture2->createTexture("../data/Resource/Images/sample.png");
	// TODO: AudioManager hoitamaan toiston kontrolleja yms
	Audio * audio = _resMngr->loadFile<Audio>("../data/Resource/Audio/samppeli.mp3");
	//Texture * tex2 = res->loadFile<Texture>("../data/Resource/Images/sample.png");
	Text * txt = _resMngr->loadFile<Text>("../data/Shaders/FragmentShaderTest.glfs");
	Audio * audio2 = _resMngr->loadFile<Audio>("../data/Resource/Audio/samppeli.mp3");
	Text * txt2 = _resMngr->loadFile<Text>("../data/Shaders/FragmentShaderTest.glfs");
	

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

graphics::Sprite * Engine::createSprite(glm::vec2 position, glm::vec2 size, int z, Color col)
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
void Engine::testInit()
{


	//Model loading
	Object3D * model = _resMngr->loadFile<Object3D>("../data/Resource/Models/boy.3ds");
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
			
		_bufMngr->addBufferData(v3D, indices3D);
		//setBufferData(vcopy, testIndicescopy);
	//	_bufMngr->drawBuffer(_shdrMngr->getActiveShader());
		//end of 3d model loading//
	
		////TEST TRIANGLE FOR DEBUG
		
	//GLfloat vertices[] = {
	//	0.5f, 0.5f, 0.0f,  // Top Right
	//	0.5f, -0.5f, 0.0f,  // Bottom Right
	//	-0.5f, -0.5f, 0.0f,  // Bottom Left
	//	-0.5f, 0.5f, 0.0f   // Top Left 
	//};
	//	for (int i = 0; i < 4; i++)
	//	{
	//		Vertex v;
	//		//if (i == 0)
	//		//{
	//			v.Position.x = vertices[i * 3];
	//			v.Position.y = vertices[i * 3 + 1];
	//			v.Position.z = vertices[i * 3 + 2];
	//		//}
	//		/*else
	//		{
	//			v.Position.x = vertices[i * 3 + 1];
	//			v.Position.y = vertices[i * 3 + 2];
	//			v.Position.z = vertices[i * 3 + 3];
	//		}*/

	//		v.Normal = glm::vec3(0,0,0);
	//		v.TexCoords = glm::vec2(0, 0);
	//		v.Color = glm::vec3(122,122,122);
	//		ver.push_back(v);
	//	}
	//
	//
	//	GLuint indices[] = {  // Note that we start from 0!
	//		3, 0, 1,  // First Triangle
	//		1, 2, 3   // Second Triangle
	//	};
	//
	//	for (int i = 0; i < 6; i++)
	//	{
	//		inds.push_back(indices[i]);
	//	}
	


		
	
		
	

		//instead of using buffermanager, let's do this here for now to see if it works
	
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).


		////VAO stuff
		//GLuint VAO;
		//glGenVertexArrays(1, &VAO);
		//glBindVertexArray(VAO);

		////VBO stuff
		//glGenBuffers(1, &VBO);
		////VBO stuff - elements/ indices
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		////vertex vector size * amount of elements * element type
		//glBufferData(GL_ARRAY_BUFFER, ver.size() *(GLuint)11 * sizeof(GLfloat), &ver[0].Position.x, GL_STATIC_DRAW);

		////Vertex Positions
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		//	(GLvoid*)0);

		////Vertex Normals
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		//	(GLvoid*)offsetof(Vertex, Vertex::Normal));

		////Vertex Texture Coords
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		//	(GLvoid*)offsetof(Vertex, Vertex::TexCoords));

		////Vertex Color
		//glEnableVertexAttribArray(3);
		//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		//	(GLvoid*)offsetof(Vertex, Vertex::Color));
		//
		////EBO stuff
		//glGenBuffers(1, &EBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(GLuint), &inds[0], GL_STATIC_DRAW);

		//VAOs.push_back(VAO);
		//EBOs.push_back(EBO);

		//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		//glBindVertexArray(0);
		////

		//_bufMngr->addBufferData(ver, inds);
		//_bufMngr->drawBuffer(_shdrMngr->getActiveShader());
		
	
		/*
		////first Cube
		//GLfloat vertices[] = {
		//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	
		//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		//	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		//	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		//	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	
		//	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		//	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		//	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	
		//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		//	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		//	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		//	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	
		//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		//	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	
		//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		//	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
		//};
		//glm::vec3 cubePositions[] = {
		//	glm::vec3(0.0f, 0.0f, 0.0f),
		//	glm::vec3(2.0f, 5.0f, -15.0f),
		//	glm::vec3(-1.5f, -2.2f, -2.5f),
		//	glm::vec3(-3.8f, -2.0f, -12.3f),
		//	glm::vec3(2.4f, -0.4f, -3.5f),
		//	glm::vec3(-1.7f, 3.0f, -7.5f),
		//	glm::vec3(1.3f, -2.0f, -2.5f),
		//	glm::vec3(1.5f, 2.0f, -2.5f),
		//	glm::vec3(1.5f, 0.2f, -1.5f),
		//	glm::vec3(-1.3f, 1.0f, -1.5f)
		//};
	
		//GLfloat vertices2[] = {
		//	0.5f, 0.5f, 0.0f,  // Top Right
		//	0.5f, -0.5f, 0.0f,  // Bottom Right
		//	-0.5f, -0.5f, 0.0f,  // Bottom Left
		//	-0.5f, 0.5f, 0.0f   // Top Left 
		//};
		//GLuint indices2[] = {  // Note that we start from 0!
		//	0, 1, 3,  // First Triangle
		//	1, 2, 3   // Second Triangle
		//};
	
	
	
		////some normals, dunno
		//std::vector<glm::vec3> normals;			
		//normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		//normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
		//normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	
		//normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
		//normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		//normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	
		//std::vector<Vertex> v;
	
		//Vertex BV1;
		//for (int i = 0; i < 36; i++)
		//{
		//	//BufferVertex BV1; temorarily outside of the for loop
	
		//	BV1.Position = glm::vec3(vertices[i * 5], vertices[i * 5 + 1], vertices[i * 5 + 2]);
		//	
		//	if (i < 36)
		//		BV1.Normal = normals[5];
		//	if (i < 30)
		//		BV1.Normal = normals[4];
		//	if (i < 24)
		//		BV1.Normal = normals[3];
		//	if (i < 18)
		//		BV1.Normal = normals[2];
		//	if (i < 12)
		//		BV1.Normal = normals[1];
		//	if (i < 6)
		//		BV1.Normal = normals[0];
	
		//	BV1.TexCoords = glm::vec2(vertices[i * 5 + 3], vertices[i * 5 + 4]);
		//	
		//	if (i < 36)
		//		BV1.Color = glm::vec3(1.0f, 1.0f, 1.0f);
		//	if (i < 30)
		//		BV1.Color = glm::vec3(1.0f, 1.0f, 0.0f);
		//	if(i < 24)
		//		BV1.Color = glm::vec3(1.0f, 0.0f, 1.0f);
		//	if (i < 18)
		//		BV1.Color = glm::vec3(1.0f, 0.0f, 0.0f);
		//	if (i < 12)
		//		BV1.Color = glm::vec3(0.0f, 1.0f, 0.0f);
		//	if (i < 6)
		//		BV1.Color = glm::vec3(0.0f, 0.0f, 1.0f);
	
		//	//BV1.Color = glm::vec3(0.0f, 0.0f, 0.0f);
	
		//	v.push_back(BV1);
		//}
	
		//std::vector<GLuint> testIndices;
		//	
		//for (int i = 0; i < 36; i++)
		//	testIndices.push_back(i);
	
		////v.push_back(BV1);
		//
		////setBufferData(v, testIndices, tex1);
		////setBufferData(v3D, indices3D, tex1);
	
		////drawTestBuffer();
		///////
	
		//////multiple cubes
		//int numCubes = 4;
		//std::vector<Vertex> vcopy;
		//std::vector<GLuint> testIndicescopy;
		//
		//for (int i = 0; i < 36 * numCubes; i++)
		//{
		//	if (testIndicescopy.size() < 36)
		//		testIndicescopy.push_back(i + testIndices.size());
		//	else if (testIndicescopy.size() < 72)
		//		testIndicescopy.push_back(i + testIndices.size());
		//	else if (testIndicescopy.size() < 108)
		//		testIndicescopy.push_back(i + testIndices.size());
		//	else if (testIndicescopy.size() < 144)
		//		testIndicescopy.push_back(i + testIndices.size());
		//	else
		//	int y = 0;
		//	else
		//		testIndicescopy.push_back(i + testIndicescopy.size());
		//}
	
		//////
	
		////multiple cubes
		////addBufferData(vcopy, testIndicescopy, tex1copy);
		////
		////single cube
		////addBufferData(v, testIndices, tex1);
	
		//int multiplier = 0;
		//multiplier = 0;
	
		//for (int i = 0; i < 36 * numCubes; i++)
		//{
		//	if (remainder(i, 36) == 0)
		//		multiplier -= 2;			
	
		//	vcopy[i].Position.x += multiplier;
		//	vcopy[i].Color = glm::vec3(1.0f, 1.0f, 1.0f);
		//}
		////vcopy.push_back(BV1);
	
		////addBufferData(vcopy, testIndicescopy);
		////setBufferData(vcopy, testIndicescopy);
		////drawTestBuffer();
	
		////lighting
		////GLuint lighting;
		////newVAO(lighting);	
	*/
	
}

void Engine::testUpdate()
{
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	//glBindVertexArray(VAOs[0]);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, (void*)0);
	//glBindVertexArray(0);


	_bufMngr->drawBuffer(_shdrMngr->getActiveShader());
	
	_grapCtx->swap();
	glPopMatrix();
}