#include "GameObject.h"
#include "ModelComponent.h"
#include "TranslateComponent.h"

GameObject::GameObject()
	:position(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f, 1.0f, 1.0f)), origin(position), destroyed(false)
{
	std::cout << "Game object created" << std::endl;
}

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

//std::vector<Mesh>* GameObject::getModelData()
//{
//	mapIter = components.find(&typeid(ModelComponent));
//	if (mapIter != components.end())
//	{
//		//std::vector<Mesh>* mesh = 
//		return dynamic_cast<ModelComponent*>(mapIter->second)->getModelMesh();
//	}
//}

void GameObject::loadModel(std::string filepath)
{
	mapIter = components.find(&typeid(ModelComponent));
	if (mapIter != components.end())
	{
		dynamic_cast<ModelComponent*>(mapIter->second)->loadModel(filepath);
	}
}

void GameObject::addComponent(Component* component)
{
	if (typeid(*component) == typeid(ModelComponent))
	{
		components.insert(std::make_pair(&typeid(*component), component));
	}
	else if (typeid(*component) == typeid(TranslateComponent))
	{
		components.insert(std::make_pair(&typeid(*component), component));
	}
	else
	{
		std::cout << "no components added!" << std::endl;
	}
}