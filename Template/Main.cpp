#include "Core.h"
#include "BufferManager.h"
#include "GraphicContext.h"

#include <ctime>

GraphicContext* gCon = new GraphicContext;
BufferManager* buff = new BufferManager;


GLfloat *arr = new GLfloat[9];
GLuint *indices = new GLuint[3];
GLuint *something = new GLuint;
bool pressed = false;
glm::vec2 mouseClickPos;
std::string nam = "vertexbuffer";

//Test Stuff
SYSTEMTIME syst;
//

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
	////window = SDL_CreateWindow("Epeli3D", 10, 30, 640, 480,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	////glcontext = SDL_GL_CreateContext(window);
	////renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//
	buff->initTest();
	buff->getShader().Use();
	buff->testBuffer();
	

}
//Game mainloop
void gameLoop()
{
	glClearColor(0.8f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	buff->testBoxUpdate();
	buff->testBuffer();
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
	if (!pressed)
	{
		if (eng->getInput()->isMousePressed(core::Mouse::left))
		{
			pressed = true;
			mouseClickPos = eng->getInput()->getMousePosition();
			SDL_Log("Mouse Left Pressed at: %f / %f", mouseClickPos.x, mouseClickPos.y);
		}
		if (eng->getInput()->isMousePressed(core::Mouse::right))
		{
			pressed = true;
			glm::vec2 movement = eng->getInput()->getMouseMovement();
			SDL_Log("Mouse Moved: %f / %f", movement.x, movement.y);
		}
	}
	else
	{
		if (eng->getInput()->isMouseReleased(core::Mouse::left))
		{
			pressed = false;
			glm::vec2 relPos = eng->getInput()->getMousePosition();
			glm::vec2 mouseDragSize = relPos - mouseClickPos;
			SDL_Log("Mouse Left Released dragged: %f / %f", mouseDragSize.x, mouseDragSize.y);
		}
		if (eng->getInput()->isMousePressed(core::Mouse::right))
		{
			pressed = false;
		}
	}
	//glClearColor(0, 255, 255, 1);
	//glClear(GL_COLOR_BUFFER_BIT);
	//SDL_Rect rects;
	//rects.x = 320;
	//rects.y = 200;
	//rects.w = 80;
	//rects.h = 80;
	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//SDL_RenderClear(renderer);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	//SDL_RenderFillRects(renderer,&rects, 1);
	//SDL_RenderPresent(renderer);
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

GLfloat* drawPoly(int sides, float radius, float scale, GLfloat rotation, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat ca)
{
	//varataan tilaa taulukoille
	GLfloat *data = new GLfloat[9 * sides + 9];
	GLuint *indices = new GLuint[3 * sides];

	GLfloat _rotation = rotation * M_PI / 180;
	GLfloat angle = _rotation;

	//alustetaan arvoja
	GLuint numberOfIndices = 0;
	GLuint numberOfElements = 0;
	GLfloat textCoordX = 0;
	GLfloat textCoordY = 0;
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat z = 0;
	int size = sides;
	int counter = 0;

	//t‰ytet‰‰n data vertex atribuuteilla, indices oikeilla koordinaateilla
	for (int i = 0; i < sides + 1; i++)
	{
		GLfloat theta = (i * 2.0f * M_PI / sides) + (M_PI) / 4 + _rotation;

		//Textuurit
		if (i != 0)
		{
			textCoordX = cos(theta + ((3 * M_PI) / 2) + _rotation) / 2 + 0.5f;
			textCoordY = sin(theta + ((3 * M_PI) / 2) + _rotation) / 2 + 0.5f;
		}
		else
		{
			textCoordX = 0.5;
			textCoordY = 0.5;
		}
		//End of Textuurit

		//Indices
		if (i != 0 && i < sides - 1)
		{
			indices[i * 3] = indices[0];
			indices[i * 3 + 1] = indices[i * 3 - 1];
			indices[i * 3 + 2] = i + 2;
			numberOfIndices += 3;
		}
		else if (i == 0)
		{
			indices[0] = 0;
			indices[1] = 1;
			indices[2] = 2;
			numberOfIndices += 3;
		}
		else
		{
			indices[i * 3] = indices[0];
			indices[i * 3 + 1] = indices[i * 3 - 1];
			indices[i * 3 + 2] = 1;
			numberOfIndices += 3;
		}
		//End of indices

		//Position
		x = posX + (radius * sin(theta)) * scale;
		y = posY + (radius * cos(theta)) * scale;

		if (i != 0)
		{
			data[i * 9] = x;
			data[i * 9 + 1] = y;
			data[i * 9 + 2] = z;
		}
		else
		{
			data[i * 9] = posX;
			data[i * 9 + 1] = posY;
			data[i * 9 + 2] = z;
		}

		data[i * 9 + 3] = cx;
		data[i * 9 + 4] = cy;
		data[i * 9 + 5] = cz;
		data[i * 9 + 6] = ca;
		data[i * 9 + 7] = textCoordX;
		data[i * 9 + 8] = textCoordY;

		counter++;
		if (counter > 3)
		{
			counter = 0;
		}

		numberOfElements += 9;
	}

	return data;
}

void initCamera()
{
	//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	//GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	//GLfloat pitch = 0.0f;
	//GLfloat lastX = 800 / 2.0;
	//GLfloat lastY = 600 / 2.0;
	//GLfloat fov = 45.0f;

	//Camera *cam = new Camera();
	//cam->init(cameraPos, cameraFront, cameraUp, yaw, pitch, lastX, lastY, fov);

}