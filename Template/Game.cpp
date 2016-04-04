#include "Game.h"

Game::Game(GLuint width, GLuint height)
	:state(GAMEACTIVE), keys(), width(width), height(height)
{
	gContex = new GraphicContext(width, height);
}

Game::~Game()
{
	delete cam;
	delete gContex;
	delete shader;
	delete renderer;
}

void Game::init()
{

	//init camera ingame
	glm::vec3 cameraPos = glm::vec3(.0f, .0f, 15.0f);
	glm::vec3 cameraFront = glm::vec3(.0f, .0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(.0f, 1.0f, .0f);

	cam = new Camera();
	//cam->setShader(&);
	cam->setView(cameraPos, cameraPos + cameraFront, cameraUp);
	cam->setProjection2D(width, height);

	GameResourceManager::loadShader("../data/shaders/VertexShader2DGame.glvs", "../data/shaders/FragmentShader2DGame.glvs", nullptr, "sprite");
	glm::mat4 projection = glm::ortho( .0f, static_cast<GLfloat>(this->width),
		static_cast<GLfloat>(this->height), .0f, -1.f, 1.f);
	GameResourceManager::getShader("sprite").use().setInt("image", 0);
	GameResourceManager::getShader("sprite").use().setMatrix4("projection", projection);

	//set render-specific controls
	renderer = new GameSpriteRender(GameResourceManager::getShader("sprite"));

	//load textures
	GameResourceManager::loadTexture("../data/Resource/Textures/dinosaur", GL_TRUE, "dinosaur");

}

void Game::update(GLfloat deltaTime)
{

}

void Game::processInput(GLfloat deltaTime)
{

}

void Game::render()
{
	glClearColor(.0f, .0f, .0f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Draw something ingame
	renderer->drawSprite(GameResourceManager::getTexture("dinosaur"),
		glm::vec2(200, 200), glm::vec2(300, 400), 45.f, glm::vec3(.0f, 1.f, .0f));
	////
	glPopMatrix();
	gContex->swap();
}

GraphicContext* Game::getGraphCon()
{
	return gContex;
}