#include "TransformComponent.h"

TransformComponent::TransformComponent()
	:Drawable(glm::vec3(0,0,0), glm::vec3(0,0,0), Color(Colors::White))
{
	modelMatrix = getModelMatrix();
}

TransformComponent::TransformComponent(glm::vec3 position)
	: Drawable(position, glm::vec3(0, 0, 0), Color(Colors::White))
{
	modelMatrix = getModelMatrix();
}

TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 origin)
	: Drawable(position, origin, Color(Colors::White))
{
	modelMatrix = getModelMatrix();
}

TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 origin, Color color)
	: Drawable(position, origin, color)
{
	modelMatrix = getModelMatrix();
}

TransformComponent::TransformComponent(glm::vec3 position, Color color)
	: Drawable(position, glm::vec3(0, 0, 0), color)
{
	modelMatrix = getModelMatrix();
}

void TransformComponent::update(float deltaTime)
{
	modelMatrix = getModelMatrix();
};

//Sets position to
void TransformComponent::moveTo(glm::vec3 to)
{
	Drawable::moveTo(to);
}

//Adds vector "by" to current position
glm::vec3 TransformComponent::moveBy(glm::vec3 by)
{
	return Drawable::moveBy(by);
}

//Rotates all axis by given values glm::vec3(x,y,z)
void TransformComponent::rotate(glm::vec3 rotateBy)
{
	Drawable::rotate(rotateBy);
}

void TransformComponent::rotateX(float degrees)
{
	Drawable::rotateX(degrees);
}

void TransformComponent::rotateY(float degrees)
{
	Drawable::rotateY(degrees);
}

void TransformComponent::rotateZ(float degrees)
{
	Drawable::rotateZ(degrees);
}

//Sets rotation of all axis to given values glm::vec3(x,y,z)
void TransformComponent::rotateTo(glm::vec3 rotations)
{
	Drawable::rotateTo(rotations);
}

void TransformComponent::scale(float scaleBy)
{
	Drawable::scale(scaleBy);
}

void TransformComponent::translate(glm::vec3 amount)
{
	modelMatrix = glm::translate(amount);
}

////Changes current color
//void changeColor(Color newColor)
//{
//	color = newColor; 
//}