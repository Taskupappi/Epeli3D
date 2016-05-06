#include "Core.h"
#include "BufferManager.h"
#include "GraphicContext.h"

#include <ctime>

//GraphicContext* gCon = new GraphicContext(800, 600);
//BufferManager* buff = new BufferManager;

bool pressed = false;
glm::vec2 mouseClickPos;
std::string nam = "vertexbuffer";
std::string key;
Camera* cam;
//Test Stuff
SYSTEMTIME syst;
//

//deltaTime
long timeNow = SDL_GetTicks();
long timeLast = 0;
float deltaTime = 0.0f;
graphics::Sprite * sprt;


//shark model 
//vertices : 5958
//faces : 9420


////

//SDL_Window *window = nullptr;
//SDL_Renderer *renderer = nullptr;
//SDL_GLContext glcontext;
core::Engine * eng = core::Engine::UI();
//Called before engine closes
void userUnInit(){};

//Game initialization code here
void gameInit()
{

	cam = new Camera();
	eng->testInit(cam, 800, 600);

	Texture * texture = eng->createTexture("../data/Resource/Images/sample.png");
	Texture * texture2 = eng->createTexture("../data/Resource/Images/sample.png");
	Texture * texture3 = eng->createTexture("../data/Resource/Images/doge.jpeg");

	glm::vec2 size = texture->getTextureSize();
	size = texture3->getTextureSize();

	// TODO: AudioManager hoitamaan toiston kontrolleja yms
	//Audio * audio = _resMngr->loadFile<Audio>("../data/Resource/Audio/samppeli.mp3");
	////Texture * tex2 = res->loadFile<Texture>("../data/Resource/Images/sample.png");
	//Text * txt = _resMngr->loadFile<Text>("../data/Shaders/FragmentShaderTest.glfs");
	//Audio * audio2 = _resMngr->loadFile<Audio>("../data/Resource/Audio/samppeli.mp3");
	//Text * txt2 = _resMngr->loadFile<Text>("../data/Shaders/FragmentShaderTest.glfs");

	//eng->createScene();	
	
	//eng->createScene();	

	//core::Scene * sc= eng->createScene();

	////sc = eng->_scnMngr->getScene(1);

	//eng->getSpriteManager()->setShader(buff->shaderManager->getActiveShader());
	//Texture * tex = nullptr;
	//Crashes with new textures
	//sprt = eng->createSprite(tex, glm::vec2(100, 100), glm::vec2(100, 100), 0, Colors::Azure);
}

//Game mainloop
void gameLoop()
{

	//deltaTime calculations
	timeNow = SDL_GetTicks();
	if (timeNow > timeLast)
	{
		deltaTime = ((float)(timeNow - timeLast)) / 1000;
		timeLast = timeNow;
	}
	////delta time calculations

	glClearColor(0.8f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (eng->getInput()->isKeyPressed(SDLK_UP))//SDLK_PRINTSCREEN))
	{
		for (auto k : eng->getInput()->_pressedKeys)
		{
			SDL_Log("Pressed Key %s", SDL_GetKeyName(k));
		}
		eng->getInput()->clearKeys();
	}

	if (eng->getInput()->isKeyPressed(SDLK_w)
		|| eng->getInput()->isKeyPressed(SDLK_s)
		|| eng->getInput()->isKeyPressed(SDLK_a)
		|| eng->getInput()->isKeyPressed(SDLK_d)
		|| eng->getInput()->isKeyPressed(SDLK_q)
		|| eng->getInput()->isKeyPressed(SDLK_e))
	{
		for (auto k : eng->getInput()->_pressedKeys)
		{
			SDL_Log("Pressed Key %s", SDL_GetKeyName(k));
			key = SDL_GetKeyName(k);
		}
		eng->getInput()->clearKeys();

		//movement with the cam
		const char* conversion = key.c_str();
		//cam->move(key.c_str(), deltaTime);
	}
	
	eng->testUpdate(cam, deltaTime, eng->getInput()->getMousePosition(), key.c_str());

	if (eng->getInput()->iskeyReleased(SDLK_w)
		|| eng->getInput()->isKeyPressed(SDLK_s)
		|| eng->getInput()->isKeyPressed(SDLK_a)
		|| eng->getInput()->isKeyPressed(SDLK_d)
		|| eng->getInput()->isKeyPressed(SDLK_q)
		|| eng->getInput()->isKeyPressed(SDLK_e))
	{
		key = ' ';
		eng->getInput()->clearKeys();
	}



	//mouseClickPos = eng->getInput()->getMousePosition();
	//cam->mouseUpdate(mouseClickPos);

	if (!pressed)
	{
		if (eng->getInput()->isMousePressed(core::Mouse::left))
		{
			pressed = true;
			
			//eng->getSpriteManager()->drawSprites();
			//SDL_Log("Mouse Left Pressed at: %f / %f", mouseClickPos.x, mouseClickPos.y);
		}
		if (eng->getInput()->isMousePressed(core::Mouse::right))
		{
			pressed = true;
			glm::vec2 movement = eng->getInput()->getMousePosition();
			//eng->getInput()->getMouseMovement();
			SDL_Log("Mouse Moved: %f / %f", movement.x, movement.y);


			//test for camera movement below
			//buff->getCamera()->mouseUpdate(movement);
		}
	}
	else
	{
		if (eng->getInput()->isMouseReleased(core::Mouse::left))
		{
			pressed = false;
			glm::vec2 relPos = eng->getInput()->getMousePosition();
			glm::vec2 mouseDragSize = relPos - mouseClickPos;
			//SDL_Log("Mouse Left Released dragged: %f / %f", mouseDragSize.x, mouseDragSize.y);
		}
		if (eng->getInput()->isMousePressed(core::Mouse::right))
		{
			pressed = false;
		}
	}
}

int main(int argc, char** argv)
{
	eng->Init();
	eng->run();
	eng->Uninit();

	//SDL_Init(SDL_INIT_EVERYTHING);

	return 0;
}