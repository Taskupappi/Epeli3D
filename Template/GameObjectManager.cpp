#include "GameObjectManager.h"
#include "ModelComponent.h"

GameObjectManager::GameObjectManager(BufferManager *buff)
{
	buffMngr = buff;
}

GameObjectManager::~GameObjectManager()
{
	for (std::vector<GameObject*>::iterator gameobject = gameObjects.begin(); gameobject != gameObjects.end(); gameobject++)
	{
		//delete *gameobject;
		//gameobject = gameObjects.erase(gameobject);
		delete (*gameobject);
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

void GameObjectManager::sendDataToBuffer()
{
	for (auto gameobject = gameObjects.begin(); gameobject != gameObjects.end(); gameobject++)
	{
		if ((*gameobject)->getComponent<ModelComponent>())
		{
			std::vector<Mesh>* data = new std::vector<Mesh>();
			//data = (*gameobject)->getModelData();

			std::vector<Mesh>::iterator modelIter;
			std::vector<Vertex>::iterator vertexIter;
			std::vector<GLuint>::iterator indicesIter;

			std::vector<Vertex> vertexData;
			std::vector<GLuint> indicesData;
			
			for (modelIter = data->begin(); modelIter != data->end(); modelIter++)
			{
				for (vertexIter = modelIter->vertices.begin(); vertexIter != modelIter->vertices.end(); vertexIter++)
				{
					vertexData.push_back((*vertexIter));
				}

				for (indicesIter = modelIter->indices.begin(); indicesIter != modelIter->indices.end(); indicesIter++)
				{
					indicesData.push_back((*indicesIter));
				}
			}

			buffMngr->addBufferData(vertexData, indicesData);
			delete data;
		} //((*gameobject)->getComponent<ModelComponent>())

		
	}//(auto gameobject = gameObjects.begin(); gameobject != gameObjects.end();)
	
}

GameObject* GameObjectManager::createGameObject()
{
	GameObject* obj = new GameObject();
	gameObjects.push_back(obj);
	return obj;
}

//GameObject* GameObjectManager::getGameObject();
//{
//
//}

std::vector<GameObject*> GameObjectManager::getGameObjects()
{
	return gameObjects;
}