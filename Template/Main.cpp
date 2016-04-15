#include "Core.h"
#include "BufferManager.h"
#include "GraphicContext.h"

#include <ctime>

GraphicContext* gCon = new GraphicContext;
BufferManager* buff = new BufferManager;

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
	//core::Scene * sc= eng->createScene();

	//buff->initBuffers();
	//buff->initShaders();	

	//buff->getBuffer("vertexbuffer")
	//buff->drawBuffer();
	//gCon->swap();
	////sc = eng->_scnMngr->getScene(1);
	buff->initTest();
	buff->shaderManager->getActiveShader()->use();
	buff->drawTestBuffer(TEST);
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

	buff->testBoxUpdate();
	buff->drawTestBuffer(TEST);
	glPopMatrix();
	gCon->swap();
	



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
		buff->getCamera()->movementUpdate(key.c_str(), deltaTime);
	}

	if (!pressed)
	{
		if (eng->getInput()->isMousePressed(core::Mouse::left))
		{
			pressed = true;
			mouseClickPos = eng->getInput()->getMousePosition();
			//SDL_Log("Mouse Left Pressed at: %f / %f", mouseClickPos.x, mouseClickPos.y);
		}
		if (eng->getInput()->isMousePressed(core::Mouse::right))
		{
			pressed = true;
			glm::vec2 movement = eng->getInput()->getMousePosition();
			//eng->getInput()->getMouseMovement();
			SDL_Log("Mouse Moved: %f / %f", movement.x, movement.y);

			
			//test for camera movement below
			buff->getCamera()->mouseUpdate(movement);
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