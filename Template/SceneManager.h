#pragma once
#ifndef SCMNGR_H
#define SCMNGR_H
#include "camera.h"
#include <vector>
namespace core
{
	class Engine;
	class Scene
	{
		friend class core::Engine;
		/**
			Scene contains camera; by default all use the same can be changed by user
			world3D contains 3d objects for the scene
			spritemanager contains sprites for the scene
			Possible:
			Skybox
		*/
	public:
		Scene(int id,Camera * camera):_id(id),_cmr(camera){};
		~Scene(){ _cmr = nullptr; }
		void use()
		{
			//TODO: Implement
		}
		Camera * getCamera(){ return _cmr; }
	protected:
		//World3D * _world;
		//SpriteManager * _sprtMngr;
		//Skybox
		Camera * _cmr;
		int _id;

	};

	class SceneManager
	{
		/**
			SceneManager manages all scenes in engine.
			Scenes are created by calling:
			createScene returns with the id of the created scene
			changeScene(int id) changes scene
			getScene(int id) gets scene
		*/
	public:
		SceneManager();
		~SceneManager();
		Scene * createScene();
		bool changeScene(int id);
		Scene * getScene(int id);
	private:
		std::vector<Scene*> _scenes;
		Camera * _defCmr;
	};
}
#endif