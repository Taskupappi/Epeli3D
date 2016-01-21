#ifndef CORE_H
#define CORE_H
void extern gameLoop();
void extern gameInit();

//SDL
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

//Glew
#define GLEW_STATIC
#include <GL/glew.h>

//Glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>


//RapidXML
#include "RapidXML/rapidxml.hpp"

//FreeType
#include <freetype-2.6.1/include/ft2build.h>
//#include FT_FREETYPE_H

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
		bool _mainInit; //Has main initialization been done
		bool _exit; //Has exit been called
		static Engine *_instance;

	};
}

#endif;