#include "Core.h"
#include "BufferManager.h"
#include "GraphicContext.h"
#include "GameObject.h"
#include "ModelComponent.h"

#include <ctime>

//GraphicContext* gCon = new GraphicContext(800, 600);
//BufferManager* buff = new BufferManager;
int vol = 0;
int vol2 = 128;
int angle = 0;
int distance = 0;
int length = 0;
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
SoundFX * FX;
SoundFX * FX2;
Music * music;
Music * music2;

Texture * texture  = nullptr;
Texture * texture2 = nullptr;
Texture * texture3 = nullptr;

GLuint  textureint,
		textureint2,
		textureint3,
		samplerint;

glm::vec3 lightPos(0.5f, 1.0f, 1.0f);

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

	//Textures
	glGenTextures(1, &textureint);
	glBindTexture(GL_TEXTURE_2D, textureint);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	////

	cam = new Camera();
	
	//eng->testInit(cam, 800, 600);
	//eng->getShaderManager()->createShader("../data/shaders/VertexShaderTest.glvs", "../data/shaders/FragmentShaderTest.glfs", "testShader");
	eng->getShaderManager()->createShader("../data/shaders/BasicLightingJ.glvs", "../data/shaders/BasicLightingJ.glfs", "testShader");
	eng->getShaderManager()->setActiveShader("testShader");

	//camera stuff
	cam->initDefault(eng->getShaderManager()->getActiveShader());
	//ModelComponent* m = new ModelComponent();
	//GameObject* kisse = eng->createGameObject();	
	//kisse->addComponent(new ModelComponent());
	//kisse->loadModel("../data/Resource/Models/cube.obj");
	//eng->getGameObjectManager()->sendDataToBuffer();

	//m->loadModel("../data/Resource/Models/cube.obj");
	Object3D * model = eng->getResources()->loadFile<Object3D>("../data/Resource/Models/cube.obj");
	//eng->getGameObjectManager()->getGameObjects().back()->loadModel();	
	//eng->getGameObjectManager()->sendDataToOpenGL();

	//eng->getGameObjectManager()->createGameObject();
	//eng->getGameObjectManager()->getGameComponents().back()->addComponent(COMPONENTID::MODEL);
	//eng->getGameObjectManager()->getGameComponents().back()->getComponent(COMPONENTID::MODEL);


	//Model loading
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
		(*color).Color = glm::vec4((GLfloat)255 / 255, (GLfloat)0 / 255, (GLfloat)0 / 255, 1.0);
	}

	//_bufMngr->addBufferData(v3D, indices3D);

	//end of model loading

	//Model loading 2
	Object3D * model2 = eng->getResources()->loadFile<Object3D>("../data/Resource/Models/cube.obj");

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
		(*color).Color = glm::vec4((GLfloat)0 / 255, (GLfloat)255 / 255, (GLfloat)0 / 255, 0.1);
		//(*color).Color = glm::vec4(0, 125, 26, 1);
	}

	//Model loading 3
	Object3D * model3 = eng->getResources()->loadFile<Object3D>("../data/Resource/Models/cube.obj");

	std::vector<Vertex> v3D3;
	std::vector<GLuint> indices3D3;

	std::vector<Mesh>::iterator modelIter3;
	std::vector<Vertex>::iterator vertexIter3;
	std::vector<GLuint>::iterator indicesIter3;

	std::vector<Mesh> mesh3;
	mesh3 = model3->getMeshVec();

	for (modelIter3 = model3->getMeshVec().begin(); modelIter3 != model3->getMeshVec().end(); modelIter3++)
	{
		for (vertexIter3 = modelIter3->vertices.begin(); vertexIter3 != modelIter3->vertices.end(); vertexIter3++)
		{
			v3D3.push_back((*vertexIter3));
		}

		for (indicesIter3 = modelIter3->indices.begin(); indicesIter3 != modelIter3->indices.end(); indicesIter3++)
		{
			indices3D3.push_back((*indicesIter3));
		}
	}

	//std::vector<Vertex>::iterator color;
	for (color  = v3D3.begin(); color != v3D3.end(); color++)
	{
		//glm::rotate((*color).Position, 50.0f, (*color).Normal);
		//(*color).Position.z -= 145.5f;
		//int r = rand() % 255;
		//int g = rand() % 255;
		//int b = rand() % 255;
		//float alpha = (((rand() % 10) + 1) / 10);
		//alpha = glm::clamp(alpha, 0.1f, 1.0f);

		//glm::rotate((*color).Position, 50.0f, (*color).Normal);
		(*color).Position -= glm::vec3(0.5f);
		(*color).Position.x -= 4.5f;
		(*color).Color = glm::vec4((GLfloat)0 / 225, (GLfloat)0 / 225, (GLfloat)255 / 225, 0.9);
		//(*color).Color = glm::vec4(0, 125, 26, 1);
	}

	eng->getBufferManager()->addBufferData(v3D, indices3D);
	eng->getBufferManager()->addBufferData(v3D2, indices3D2);
	eng->getBufferManager()->addBufferData(v3D3, indices3D3);
	//_bufMngr->updateData();

	eng->getBufferManager()->bindBuffers();

	////lighting
	////GLuint lighting;
	////newVAO(lighting);	
	////
	Texture * texture = eng->createTexture("../data/Resource/Images/sample.png");
	Texture * texture2 = eng->createTexture("../data/Resource/Images/sample.png");
	Texture * texture3 = eng->createTexture("../data/Resource/Images/doge.jpeg");

	glm::vec2 size = texture->getTextureSize();
	size = texture3->getTextureSize();

	// TODO: AudioManager hoitamaan toiston kontrolleja yms
	FX = eng->createSoundEffect("../data/Resource/Audio/samppeli.mp3");
	FX2 = eng->createSoundEffect("../data/Resource/Audio/hey.wav");
	//length = FX2->getLength();

	music = eng->createMusic("../data/Resource/Audio/hungerland.wav");
	music2 = eng->createMusic("../data/Resource/Audio/moap.flac");
	//eng->createScene();	
	
	//eng->createScene();	

	//core::Scene * sc= eng->createScene();

	////sc = eng->_scnMngr->getScene(1);

	//eng->getSpriteManager()->setShader(buff->shaderManager->getActiveShader());
	//Texture * tex = nullptr;
	//Crashes with new textures
	sprt = eng->createSprite(texture3, glm::vec2(100, 100), glm::vec2(100, 100), 0, Colors::Azure);
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

	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
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
	
	
	//eng->testUpdate(cam, deltaTime, eng->getInput()->getMousePosition(), key.c_str());
	eng->getShaderManager()->useActiveShader();
	GLint objectColorLoc = eng->getShaderManager()->getActiveShader()->getUniformLocation("objectColor");
	GLint lightColorLoc = eng->getShaderManager()->getActiveShader()->getUniformLocation("lightColor");
	GLint lightPosLoc = eng->getShaderManager()->getActiveShader()->getUniformLocation("lightPos");
	GLint viewPosLoc = eng->getShaderManager()->getActiveShader()->getUniformLocation("viewPos");
	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);	
	glUniform3f(viewPosLoc, cam->getPosX(), cam->getPosY(), cam->getPosZ());

	GLfloat radius = 10.0f;
	GLfloat camX = sin(deltaTime) * radius;
	GLfloat camZ = cos(deltaTime) * radius;

	//glm::mat4 view;
	//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	cam->mouseUpdate(eng->getInput()->getMousePosition());
	cam->move(key.c_str(), deltaTime);
	//cam->setViewMatrix(view);

	/*glGenSamplers(1, &samplerint);
	glBindSampler(0, samplerint);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureint);
	glUniform1i(glGetUniformLocation(eng->getShaderManager()->getActiveShader()->getShaderProgram(), "texture1"), 0);*/

	cam->passMatricesToShader(eng->getShaderManager()->getActiveShader());

	//eng->getBufferManager()->updateData();
	//eng->getGameObjectManager()->draw();
	eng->getBufferManager()->drawBuffer();

	eng->getGraphicContext()->swap();
	glPopMatrix();

	////eng->testUpdate(cam, deltaTime, eng->getInput()->getMousePosition(), key.c_str());
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
	if(eng->getInput()->isKeyPressed(SDLK_o))//Draws sprites
	{
		eng->getSpriteManager()->drawSprites();
	}
	if (eng->getInput()->isKeyPressed(SDLK_p))//Play sound
	{
		vol = 128;
		FX->setVolume(vol);
		FX->setSoundDirection(1, angle, 1);
		FX->playSound(-1, 0);
		angle += 90;
		if (angle == 360)
			angle = 0;
	}
	if (eng->getInput()->isKeyPressed(SDLK_l))//Play sound
	{
		FX2->setVolume(vol2);
		FX2->playSound(-1, 0);
		
	}
	if (eng->getInput()->isKeyPressed(SDLK_k))//Play sound
	{
		FX->setVolume(vol2);
		FX->playSound();
	}

	if (eng->getInput()->isKeyPressed(SDLK_n))
		music->playMusic(-1);

	if (eng->getInput()->isKeyPressed(SDLK_m))
		music->fadeInMusic(2000, -1);
	if (eng->getInput()->isKeyPressed(SDLK_b))
		music->stopMusic();
}

int main(int argc, char** argv)
{
	eng->Init();
	eng->run();
	eng->Uninit();

	//SDL_Init(SDL_INIT_EVERYTHING);

	return 0;
}