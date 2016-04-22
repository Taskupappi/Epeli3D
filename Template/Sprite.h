#ifndef SPRITE_H
#define SPRITE_H
#include "Drawable.h"
#include <unordered_map>
//#include "Texture.h"
#include <vector>
#include "BufferManager.h"
#include <glm/vec3.hpp>
#include "Shader.h"
#include "Color.h"
#include "Texture.h"
class Texture;
namespace graphics
{
	//class Texture;
	//class Shader;//TODO: Placeholder
	class Sprite :
		public Drawable
	{
	friend class SpriteManager;
	public:

	protected:
<<<<<<< HEAD
		Sprite(glm::vec3 position, float width, float height, glm::vec3 origin, Shader * shdr, Texture * tex, GLclampf w, GLclampf h) :
			Drawable(position,origin), _width(width), _height(height), _shdr(shdr), _tex(tex), _texW(w), _texH(h)
=======
		Sprite(glm::vec3 position, int width, int height, glm::vec3 origin,Color col, Shader * shdr, Texture * tex, GLclampf w, GLclampf h) :
			Drawable(position,origin,col), _width(width), _height(height), _shdr(shdr), _tex(tex), _texW(w), _texH(h)
>>>>>>> refs/remotes/origin/master
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

		const GLchar* defVertexShader =
			"attribute vec2 position;\n"
			"attribute vec2 texture;\n"
			"uniform mat4 world;\n"
			"uniform mat4 window;\n"
			"uniform mat4 view;\n"
			"varying vec2 UV;\n"
			"attribute vec4 color;\n"
			"varying vec4 varyCol;\n"
			"void main() {\n"
			"	UV = texture;\n"
			"	varyCol = color; \n"
			"   gl_Position =  window * vec4(position, 0, 1);\n"
			"}\n";
		const GLchar* defFragmentShader =
			"varying lowp vec4 varyCol;\n"
			"varying lowp vec2 UV;\n"
			"uniform sampler2D sampler;\n"
			"void main()\n"
			"{\n"
			"   gl_FragColor = texture2D(sampler, UV) + varyCol;\n"
			"}\n";
	};

	
}
#endif

