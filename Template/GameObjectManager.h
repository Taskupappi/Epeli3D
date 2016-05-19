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
	 GameObject* createGameObject();
	 
	 std::vector<GameObject*> getGameComponents();
	//create game object
	//void createGO();

protected:
	std::vector<GameObject*> gameObjects;
	//std::vector<GameObject*> destroyedGameObjects;
};

#endif