#ifndef SPRITEMNGR_H
#define SPRITEMNGR_H

#include "Sprite.h"
namespace graphics
{
	class SpriteManager
	{
	public:
		///Creates sprites
		Sprite * createSprite(glm::vec3 pos, glm::vec2 size, glm::vec2 origin, Texture * texture, GLclampf texWidth, GLclampf texHeight);
		///Draws all created sprites
		void drawSprites();
	private:
		//Created by engine
		SpriteManager(BufferManager * bfr):_bfr(bfr){};
		~SpriteManager();

		std::unordered_map<Texture *, std::vector<Sprite*>>::iterator it;
		std::unordered_map<Texture *, std::vector<Sprite*>> _sprites;
		BufferManager * _bfr;
	};
	
}
#endif