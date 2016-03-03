#ifndef SPRITE_H
#define SPRITE_H
#include "Drawable.h"
#include <unordered_map>
#include "Texture.h"
#include <vector>
#include "BufferManager.h"
#include <glm/vec3.hpp>
#include "TempShader.h"

namespace graphics
{
	//class Shader;//TODO: Placeholder
	class Sprite :
		public Drawable
	{
	friend class SpriteManager;
	public:

	protected:
		Sprite(glm::vec3 position, int width, int height, glm::vec3 origin, Shader * shdr, Texture * tex, GLclampf w, GLclampf h) :
			Drawable(position,origin), _width(width), _height(height), _shdr(shdr), _tex(tex), _texW(w), _texH(h)
		{};

		Sprite(){};
		~Sprite(){};

		//Returns sprite corner points std::vector3[4]
		glm::vec3 * getVertices();
	private:
		int _width, _height;
		glm::vec2 * getTexBounds();
		//Width and height of the texture to be used
		//0.5 / 0.5 uses 1/4 of the texture
		GLclampf _texW, _texH;
		Texture * _tex;
		Shader * _shdr; //TODO: Need to use the correct shader class
		glm::vec3 _positions[4];
	};

	
}
#endif

