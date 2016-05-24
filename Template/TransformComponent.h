#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Component.h"
#include "Drawable.h"

class TransformComponent : public Component, public graphics::Drawable
{
public:
	TransformComponent();
	TransformComponent(glm::vec3 position);
	TransformComponent(glm::vec3 position, glm::vec3 origin);
	TransformComponent(glm::vec3 position, glm::vec3 origin, Color color);
	TransformComponent(glm::vec3 position, Color color);
	~TransformComponent(){};

	void moveTo(glm::vec3 to);
	void moveBy(glm::vec3 by);
	void move(glm::vec3 amount);
	void rotate(glm::vec3 rotateBy);
	void rotateX(float degrees);
	void rotateY(float degrees);
	void rotateZ(float degrees);
	void rotateTo(glm::vec3 rotations);
	void scale(float scaleBy);
	void translate(glm::vec3 amount);
	glm::mat4 getModelMatrix(){ return getTransfMat(); }

	//void translate(glm::vec3 newPosition){ model = glm::translate(model, newPosition); }
	//void rotate(const float angle, const glm::vec3 axis){ model = glm::rotate(model, angle, axis); }
	//glm::mat4 getModelMatrix(){ return model; }

private:
	glm::mat4 modelMatrix;
	void update(float deltaTime);
	
	//glm::mat4 model;
};
#endif