#ifndef TRANSLATECOMPONENT_H
#define TRANSLATECOMPONENT_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Component.h"

class TranslateComponent : public Component
{
public:
	TranslateComponent(){};
	~TranslateComponent(){};
	void translate(glm::vec3 newPosition){ model = glm::translate(model, newPosition); }
	void rotate(const float angle, const glm::vec3 axis){ model = glm::rotate(model, angle, axis); }
	glm::mat4 getModelMatrix(){ return model; }
private:
	void update(float deltaTime){};
	glm::mat4 model;
};
#endif