#include "GameSpriteRenderer.h"

GameSpriteRender::GameSpriteRender(GameShader shader)
{

}

GameSpriteRender::~GameSpriteRender()
{

}

void GameSpriteRender::drawSprite(GameTexture2D &texture, glm::vec2 position,
	glm::vec2 size , GLfloat rotate, glm::vec3 color)
{
	this->shader.use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, .0f));
	model = glm::translate(model, glm::vec3(.5f * size.x, .5f * size.y, .0f));
	model = glm::rotate(model, rotate, glm::vec3(.0f, .0f, 1.f));
	model = glm::scale(model, glm::vec3(size, 1.f));

	this->shader.setMatrix4("model", model);
	this->shader.setVec3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void GameSpriteRender::initRenderData()
{
	GLuint VBO;
	GLfloat vertices[] = {
		//pos			//tex
		.0f, 1.f, 0.f, 1.f,
		1.f, .0f, 1.f, 0.f,
		.0f, .0f, .0f, .0f,

		.0f, 1.f, .0f, .0f,
		1.f, 1.f, 1.f, 1.f,
		1.f, .0f, 1.f, .0f
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &this->quadVAO);
	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

}

