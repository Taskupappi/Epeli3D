#ifndef GAME_H
#define GAME_H

#include "Core.h"
#include "GraphicContext.h"
#include "Camera.h"
#include "BufferManager.h"
#include "Input.h"
#include "TempShader.h"

#include <GL/glew.h>
#include <ctime>
#include <vector>
#include <iostream>
#include <array>
#include <sstream>  

#include <ctime>
#include <glm\gtc\type_ptr.hpp>

#include <glm\glm.hpp>

#include "amp.h"
#include "TempShader.h"
#include "Camera.h"


enum GateState{
	GAMEACTIVE,
	GAMEMENU,
	GAMEWIN
};

class Game
{
public:
	Game(GLuint width, GLuint height);
	~Game();
	//init
	void init();
	//gameloop
	void processInput(GLfloat dt);
	void update(GLfloat dt);
	void render();

private:
	//GameState State;
	GLboolean keys[1024];
	GLuint Width, Height;

};
#endif