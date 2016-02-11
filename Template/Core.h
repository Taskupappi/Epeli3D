#ifndef CORE_H
#define CORE_H
void extern gameLoop();
void extern gameInit();
void extern userUnInit();
#include <stdio.h>

//Glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
//SDL
#include <SDL/SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
//RapidXML
#include "RapidXML/rapidxml.hpp"

//FreeType
#include <freetype-2.6.1/include/ft2build.h>
//#include FT_FREETYPE_H
#include "SceneManager.h"
#include "TestiFoo.h"
#include "ResourceManager.h"
#include "ResourceMap.h"
#include "Input.h"
//Assimp
#include <assimp/Importer.hpp>

namespace core
{
	class Engine
	{
	public:

		static Engine* UI();
		void Init();
		void Uninit();
		bool run();
		void userInit();
		void quit(){ _exit = true; }
		Scene * createScene()
		{
			return nullptr;
			//return _scnMngr->createScene(); 
		}
		//Needs to read managers from scene and set them as current
		bool useScene(Scene * sc){ return true; }
		core::Input * getInput(){ return _input; }
	protected:
		virtual ~Engine();
		Engine();

		//TO DO:
		//textureManager = nullptr;
		//sceneManager = nullptr;
		//shaderManager = nullptr;
		//spriteeManager = nullptr;
		//audioManager = nullptr;
		//3DobjectManager = nullptr;
		//bufferManager = nullptr;
	private:
		//ResourceManager *_resMngr;
		core::Input * _input;
		core::SceneManager *_scnMngr;
		bool _mainInit; //Has main initialization been done
		bool _exit; //Has exit been called
		static Engine *_instance;
		void processInput();
	};
}

#endif;