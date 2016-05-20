#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

//#include "Sprite.h"
//#include "Model.h"

#include "Shader.h"
//#include "Object3D.h"
#include <vector>
#include<iostream>
#include <map>

//#include "Component.h"
//#include "ModelComponent.h"
//#include "TranslateComponent.h"

//class Shader;
class Object3D;
class Component;
class ModelComponent;
class TranslateComponent;
class Mesh;

class GameObject
{
public:
	GameObject();
	//GameObject(std::string name);
	//GameObject(std::string modelPath);
	//GameObject(std::string spritePath);
	~GameObject();

	void setSprite(std::string filepath);
	void setModel(std::string filepath);

	void update(float deltaTime);
	void destroy();	
	bool isDestroyed() { return this->destroyed; }

	std::vector<Mesh>* getModelData();
	//Object3D* getModelData();
	//gameobject
	void loadModel(std::string filepath);
	
	void setPosition(glm::vec3 newPosition){ position = newPosition; }

	void addComponent(Component* component);
	
	//Component* getComponent(Component a);

	template<typename T>
	T* getComponent()
	{
		mapIter = components.find(&typeid(T));
		if (mapIter != components.end())
		{
			return dynamic_cast<T*>(mapIter->second);
		}
		return nullptr;
	}

	template<typename T>
	T* removeComponent()
	{
		mapIter = components.find(&typeid(T));
		if (mapIter != compoents.end())
		{
			delete mapIter->second;
			components.erase(mapIter);
		}
	}

	//void setRotation(float angle);
	// move the entity relatively to its current position
	//void Move(glm::vec3 Movement){/*TODO: IMPLEMENT*/ }

private:
	glm::vec3 scale,
			 position,
			 origin;

	//graphics::Sprite* sprite;
	float rotation;
	glm::mat4 modelMatrix;
	bool destroyed;
	std::map<const std::type_info*, Component*> components;
	std::map<const std::type_info*, Component*>::const_iterator mapIter;;
	//ModelComponent* model;
	//TranslateComponent* translate;
};
#endif