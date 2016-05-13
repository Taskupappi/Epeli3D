#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	 void update(float deltaTime);
	 void draw(Shader* shader);

	//add gameobject to the manager
	 GameObject* addGO(GameObject* gameObject);

	//create game object
	//void createGO();

private:
	std::vector<GameObject*> gameObjects;
	//std::vector<GameObject*> destroyedGameObjects;
};

#endif