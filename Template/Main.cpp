#include "Core.h"
#include "BufferManager.h"
#include "GraphicContext.h"


GraphicContext* gCon = new GraphicContext;
BufferManager* buff = new BufferManager;


GLfloat *arr = new GLfloat[9];
GLuint *indices = new GLuint[3];
GLuint *something = new GLuint;
float rotation = 0;
bool pressed = false;
glm::vec2 mouseClickPos;
std::string nam = "vertexbuffer";

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

	buff->testBuffer();
	
	//buff->initTest();
	//arr[0] = 1.0f;
	//arr[1] = 2.0f;
	//arr[3] = 1.0f;
	//arr[4] = 0.2f;
	//arr[5] = 1.0f;
	//arr[6] = 0.4f;
	//arr[7] = 1.0f;
	//arr[8] = 1.0f;
	//arr[9] = 0.0f;

	//indices[0] = 1;
	//indices[1] = 2;
	//indices[2] = 3;

	//*something = 3;
	//
	//buff->addVertexData(arr, 9);
	//buff->addIndexData(indices, something);
}
//Game mainloop
void gameLoop()
{
	
	// Create transformations
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	model = glm::rotate(model, (GLfloat)time(0) * 50.0f, glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));		
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

	// Camera/View transformation
	GLfloat radius = 10.0f;
	GLfloat camX = sin(time(0)) * radius;
	GLfloat camZ = cos(time(0)) * radius;
	view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// Projection 
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

	// Get uniform location
	GLint modelLoc = glGetUniformLocation(buff->getShader().GetShaderProgram(), "model");
	GLint viewLoc = glGetUniformLocation(buff->getShader().GetShaderProgram(), "view");
	GLint projLoc = glGetUniformLocation(buff->getShader().GetShaderProgram(), "projection");

	// Pass them to the shaders
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//temporary rotation
	glPushMatrix();
	glRotatef(rotation, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation, 1.0f, 1.0f, 1.0f);
	rotation += 0.25f;
	if (rotation > 360)
		rotation = 0;

	//buff->drawBuffer(buff->getBuffer(nam));

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