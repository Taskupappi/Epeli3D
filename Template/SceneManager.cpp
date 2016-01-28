#include "SceneManager.h"
using namespace core;
bool SceneManager::changeScene(int id)
{
	if (id > _scenes.size() + 1)
		return false;
	_scenes[id]->use();
	return true;
}
Scene * SceneManager::getScene(int id)
{
	return _scenes[id];
}
Scene * SceneManager::createScene()
{
	_scenes.push_back(new Scene(0, _defCmr));
	return _scenes[_scenes.size()-1];
}
SceneManager::SceneManager()
{
	_defCmr = new Camera();
	_scenes.push_back(new Scene(0, _defCmr));

}

SceneManager::~SceneManager()
{
	for (Scene * sc : _scenes)
		delete sc;
	_scenes.clear();
	delete _defCmr;
	_defCmr = nullptr;
}