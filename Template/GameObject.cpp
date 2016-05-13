#include "GameObject.h"

GameObject::GameObject()
	:position(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f, 1.0f, 1.0f)), origin(position), destroyed(false)
{
	std::cout << "Game object created" << std::endl;
}

//GameObject::GameObject(std::string name)
//	: position(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f, 1.0f, 1.0f)), origin(position), isDestroyed(false)
//{
//
//}

//GameObject::GameObject(std::string modelPath)
//{
//
//}
//
//GameObject::GameObject(std::string spritePath)
//{
//
//}

GameObject::~GameObject()
{

}

void GameObject::update(float deltaTime)
{

}

void GameObject::destroy()
{
	this->destroyed = true;
}