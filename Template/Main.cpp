#include "Core.h"
#include "BufferManager.h"
#include "GraphicContext.h"

#include <ctime>

//GraphicContext* gCon = new GraphicContext;
//BufferManager* buff = new BufferManager;

bool pressed = false;
glm::vec2 mouseClickPos;
std::string nam = "vertexbuffer";
std::string key;

//Test Stuff
SYSTEMTIME syst;
//

//deltaTime
long timeNow = SDL_GetTicks();
long timeLast = 0;
float deltaTime = 0.0f;
graphics::Sprite * sprt;


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
	eng->createScreen(800, 600);
	eng->testInit();

	Texture * texture = eng->createTexture("../data/Resource/Images/sample.png");
	Texture * texture2 = eng->createTexture("../data/Resource/Images/sample.png");
	Texture * texture3 = eng->createTexture("../data/Resource/Images/doge.jpeg");

	glm::vec2 size = texture->getTextureSize();
	size = texture3->getTextureSize();

	// TODO: AudioManager hoitamaan toiston kontrolleja yms
	Audio * audio = eng->createAudio("../data/Resource/Audio/samppeli.mp3");
	////Texture * tex2 = res->loadFile<Texture>("../data/Resource/Images/sample.png");
	//Text * txt = _resMngr->loadFile<Text>("../data/Shaders/FragmentShaderTest.glfs");
	//Audio * audio2 = _resMngr->loadFile<Audio>("../data/Resource/Audio/samppeli.mp3");
	//Text * txt2 = _resMngr->loadFile<Text>("../data/Shaders/FragmentShaderTest.glfs");
	
	//eng->createScene();
	
	
	//core::Scene * sc= eng->createScene();

	//buff->initBuffers();
	//buff->initShaders();	

	//buff->getBuffer("vertexbuffer")
	//buff->drawBuffer();
	//gCon->swap();
	////sc = eng->_scnMngr->getScene(1);


	//buff->initTest();
	//buff->shaderManager->getActiveShader()->use();
	//buff->drawTestBuffer();


	//eng->getSpriteManager()->setShader(buff->shaderManager->getActiveShader());
	//sprt = eng->createSprite(glm::vec2(100, 100), glm::vec2(100, 100), 0, Colors::Azure, nullptr);
}

//Game mainloop
void gameLoop()
{
	//deltaTime calculations
	if (timeNow > timeLast)
	{
		deltaTime = ((float)(timeNow - timeLast)) / 1000;
		timeLast = timeNow;
	}
	////delta time calculations

	glClearColor(0.8f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	eng->testUpdate();
	//buff->testBoxUpdate();
	//buff->drawTestBuffer();
	//glPopMatrix();
	//gCon->swap();

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
		//buff->getCamera()->move(key.c_str(), deltaTime);
	}

	if (!pressed)
	{
		if (eng->getInput()->isMousePressed(core::Mouse::left))
		{
			pressed = true;
			mouseClickPos = eng->getInput()->getMousePosition();
			//eng->drawSprites();
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