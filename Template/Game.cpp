#include "Game.h"

Game::Game(GLuint width, GLuint height)
	:State(GAMEACTIVE), keys(), Width(width), Height(height)
{
	gContex = new GraphicContext(width, height);
}

Game::~Game()
{
	delete cam;
	delete gContex;
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
}

void Game::update(GLfloat deltaTime)
{

}

void Game::processInput(GLfloat deltaTime)
{

}

void Game::render()
{
	glClearColor(.0f, .0f, .0f, .0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Draw something ingame

	////
	glPopMatrix();
	gContex->swap();
}

GraphicContext* Game::getGraphCon()
{
	return gContex;
}