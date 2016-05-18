#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	for (std::vector<GameObject*>::iterator gameobject = gameObjects.begin(); gameobject != gameObjects.end(); gameobject++)
	{
		delete *gameobject;
		gameobject = gameObjects.erase(gameobject);
	}
}

void GameObjectManager::update(float deltaTime)
{
	//delete destroyed objects
	for (std::vector<GameObject*>::iterator gameobject = gameObjects.begin(); gameobject != gameObjects.end();)
	{
		if ((*gameobject)->isDestroyed())
		{
			delete *gameobject;
			gameobject = gameObjects.erase(gameobject);
			//destroyedGameObjects.push_back((*gameobject));
		}
		else
		{
			gameobject++;
		}		
	}

	//update gameobjects
	for (std::vector<GameObject*>::iterator gameobject = gameObjects.begin(); gameobject != gameObjects.end();)
	{
		(*gameobject)->update(deltaTime);
	}
}

void GameObjectManager::draw(Shader* shader)
{
	for (auto gameobject = gameObjects.begin(); gameobject != gameObjects.end();)
	{
		//(*gameobject)->draw(shader);
	}
}

GameObject* GameObjectManager::createGameObject()
{
	GameObject* obj = new GameObject();
	gameObjects.push_back(obj);
	return obj;
}

std::vector<GameObject*> GameObjectManager::getGameComponents()
{
	return gameObjects;
}

//void GameObjectManager::createGameObject()
//{
//
//}
