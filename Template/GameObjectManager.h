#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "GameObject.h"
class BufferManager;
class GameObject;

class GameObjectManager
{
public:
	GameObjectManager(BufferManager *buff);
	~GameObjectManager();

	 void update(float deltaTime);

	 Object3D* getModelData();
	 void sendDataToBuffer();
	//add gameobject to the manager
	 GameObject* createGameObject();
	 //GameObject* getGameObject();
	 std::vector<GameObject*> getGameObjects();
	//create game object
	//void createGO();
protected:
	BufferManager* buffMngr;
	std::vector<GameObject*> gameObjects;
	//std::vector<GameObject*> destroyedGameObjects;
	std::vector<Mesh>* data;
};

#endif