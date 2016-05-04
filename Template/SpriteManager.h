#ifndef SPRITEMNGR_H
#define SPRITEMNGR_H

#include "Sprite.h"
#include "BufferManager.h"
#include "Texture.h"
#include "ShaderManager.h"

class Texture;
namespace core
{
	class Engine;
}
class BufferManager;
namespace graphics
{
	class Sprite;
	class SpriteManager
	{
		friend class core::Engine;
	public:
		///Creates sprites
		graphics::Sprite * createSprite(glm::vec3 pos, glm::vec2 size, glm::vec2 origin, Color col, Texture * texture, GLclampf texWidth, GLclampf texHeight);
		///Draws all created sprites
		void drawSprites();
		void setShader(Shader * toSet){ _shdr = toSet; }
	protected:
		//Created by engine
		SpriteManager(BufferManager * bfr, ShaderManager * shdr) :_shdrMngr(shdr), _bfr(bfr), _shdr(nullptr)
		{
			//TODO: Need to use main buffer..
			_bfr = new BufferManager();
			//_shdrMngr->createShader("../data/shaders/VertexShaderLamp.glvs", "../data/shaders/FragmentShaderLamp.glfs", "testLampShader");
			//_shdrMngr->createShader("../data/shaders/VertexShaderLightSource.glvs", "../data/shaders/FragmentShaderLightSource.glfs", "testShader");
		};
		~SpriteManager();
	private:
		void setSpriteShader()
		{
			if(!_shdr)
				_shdr = _shdrMngr->createShader("../data/shaders/VertexSprite.glvs", "../data/shaders/FragmentSprite.glfs", "spriteShader");
			if(_shdrMngr->getActiveShader() != _shdr)
				oldShdr = _shdrMngr->getActiveShader();
			_shdrMngr->setActiveShader("spriteShader");
			_shdr->use();
		}
		//Sorts sprites by z value		
		void batchSprites(std::vector<Sprite*> *spritesToBatch);
		std::unordered_map<Texture *, std::vector<Sprite*>>::iterator it;
		std::unordered_map<Texture *, std::vector<Sprite*>> _sprites;
		BufferManager * _bfr;
		ShaderManager* _shdrMngr;
		Shader * _shdr;
		Shader * oldShdr;
	};
	
}
#endif