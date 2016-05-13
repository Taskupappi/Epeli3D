#include "SpriteManager.h"
using namespace graphics;
Sprite * SpriteManager::createSprite(glm::vec3 pos, glm::vec2 size, glm::vec2 origin, Color col, Texture * texture, GLclampf TexWidth = 1.0, GLclampf TexHeight = 1.0)
{
	Shader * shdr = nullptr; //TODO: needs to get default shader
	Sprite * sprt = nullptr;
	//it = _sprites.begin();
	if(_sprites.size() != 0)
	{
		for(it = _sprites.begin(); it != _sprites.end(); it++)
		{
			if(it->first == texture)
			{
				sprt = new Sprite(pos, size.x, size.y, glm::vec3(origin, 0.0f),col, shdr, texture, TexWidth, TexHeight);
				it->second.push_back(sprt);
				return sprt;
			}
		}
	}
	std::vector<Sprite*> sprts;
	sprt = new Sprite(pos, size.x, size.y, glm::vec3(origin, 0.0f), col, shdr, texture, TexWidth, TexHeight);
	sprts.push_back(sprt);
	_sprites.insert(std::make_pair(texture, sprts));
	
	return sprt;
}


void SpriteManager::drawSprites()
{
	Texture * tex = nullptr;
	Shader * shdr = _shdr; //Default shader
	setSpriteShader();
	//Need texture sampler
	Sprite * sprt;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indecis;	
	std::vector<Sprite*>::iterator sIt;
	//Gets all sprites with same texture

	for(it = _sprites.begin(); it != _sprites.end(); it++)
	{
		if(!it->first)
		{
			//it->first->bindTexture();
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, 0);
		}
		// TODO: needs to bind texture here
		//it->first->bind();
		//Should check for changes before batching
		batchSprites(&it->second);
		for(sIt = it->second.begin(); sIt != it->second.end(); sIt++)
		{
			sprt = *sIt;
			/*
			if(sprt->_shdr != shdr) //Changes uses different shader if it has changed
			{
				shdr = sprt->_shdr;
				shdr->use(); //TODO: Needs to call shader use once implemented
			}
			*/

			//returns vec3[4]
			glm::vec3 * points = sprt->getVertices();
			glm::vec2 texBounds;//TODO: = sprt->getTexBounds();
			glm::vec4 color = sprt->color.getAsOGLVec();
			for(int i = 0; i < 4; i++)
			{
				Vertex vertice;
				vertice.Position = points[i];
				vertice.Normal = glm::vec3(0, 0, 1);
				vertice.TexCoords = texBounds;
				vertice.Color = glm::vec4(color.r,color.g,color.b, 1.0f);
				vertices.push_back(vertice);
			}
			indecis.push_back(0);
			indecis.push_back(1);
			indecis.push_back(3);

			indecis.push_back(1);
			indecis.push_back(2);
			indecis.push_back(3);

			_bfr->addBufferData(vertices, indecis);
		}
		_bfr->drawBuffer();
		_bfr->clearBuffers();
		//TODO: unbind texture
		//it->first->unbind();
	}
}
void SpriteManager::batchSprites(std::vector<Sprite*> *toBatch)
{
	auto sortSprt = [](Sprite * s1, Sprite * s2)
	{
		if(s1->getPosition().z >= s2->getPosition().z)
			return true;
		return false;
	};

	std::sort(toBatch->begin(), toBatch->end(), sortSprt);

	return;
}
SpriteManager::~SpriteManager()
{
	std::vector<Sprite*> *sprts;
	std::vector<Sprite*>::reverse_iterator rIt;

	for(it = _sprites.end(); it != _sprites.begin(); it--)
	{
		sprts = &it->second;
		for(auto sprt = sprts->end(); sprt != sprts->begin(); sprts--)
		{
			delete sprts;
		}
		it->second.clear();
	}
	_sprites.clear();
}

