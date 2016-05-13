#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

//#include "Sprite.h"
//#include "Model.h"

#include "Shader.h"
//#include "Object3D.h"
#include <vector>
#include<iostream>

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

	//gameobject
	void loadModel(std::string filepath);

	void setPosition(glm::vec3 newPosition){ position = newPosition; }
	
	
	//void setRotation(float angle);
	// move the entity relatively to its current position
	//void Move(glm::vec3 Movement){/*TODO: IMPLEMENT*/ }

private:
	glm::vec3 scale,
			 position,
			 origin;

	//graphics::Sprite* sprite;
	//Object3D* model;
	float rotation;
	glm::mat4 modelMatrix;
	bool destroyed;

//protected:
//	virtual void onUpdate();
//	virtual void onDraw() = 0;
};
#endif