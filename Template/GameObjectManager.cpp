#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{

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

GameObject* GameObjectManager::addGO(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
	return gameObject;
}

//void GameObjectManager::createGameObject()
//{
//
//}
