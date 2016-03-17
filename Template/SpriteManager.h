#ifndef SPRITEMNGR_H
#define SPRITEMNGR_H

#include "Sprite.h"
#include "BufferManager.h"
namespace core
{
	class Engine;
}
namespace graphics
{
	class SpriteManager
	{
		friend class core::Engine;
	public:
		///Creates sprites
		Sprite * createSprite(glm::vec3 pos, glm::vec2 size, glm::vec2 origin, Texture * texture, GLclampf texWidth, GLclampf texHeight);
		///Draws all created sprites
		void drawSprites();
	protected:
		//Created by engine

		SpriteManager(BufferManager * bfr) :_bfr(bfr){};
		~SpriteManager();
	private:
		//Sorts sprites by z value		
		void batchSprites(std::vector<Sprite*> *spritesToBatch);
		std::unordered_map<Texture *, std::vector<Sprite*>>::iterator it;
		std::unordered_map<Texture *, std::vector<Sprite*>> _sprites;
		BufferManager * _bfr;
	};
	
}
#endif