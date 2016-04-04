#ifndef GSR_H
#define GSR_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "GameTexture2D.h"
#include "GameShader.h"

class GameSpriteRender
{
public:
	GameSpriteRender(GameShader shader);
	~GameSpriteRender();
	void drawSprite(GameTexture2D &texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10,10), GLfloat rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));
private:
	void initRenderData();
	
	GameShader shader;
	GLuint quadVAO;
};

#endif