#include "SpriteManager.h"
using namespace graphics;
Sprite * SpriteManager::createSprite(glm::vec3 pos, glm::vec2 size, glm::vec2 origin, Texture * texture, GLclampf TexWidth = 1.0, GLclampf TexHeight = 1.0)
{
	Shader * shdr = nullptr; //TODO: needs to get default shader
	Sprite * sprt = nullptr;
	for(it = _sprites.begin(); it != _sprites.end(); it++)
	{
		if(it->first == texture)
		{
			sprt = new Sprite(pos, size.x, size.y, glm::vec3(origin, 0.0f), shdr, texture, TexWidth, TexHeight);
			it->second.push_back(sprt);
			return sprt;
		}
	}
	std::vector<Sprite*> sprts;
	sprt = new Sprite(pos, size.x, size.y, glm::vec3(origin, 0.0f), shdr, texture, TexWidth, TexHeight);
	sprts.push_back(sprt);
	_sprites.insert(std::make_pair(texture, sprts));
	return sprt;
}


void SpriteManager::drawSprites()
{
	Texture * tex = nullptr;
	Shader * shdr = nullptr;
	Sprite * sprt;

	std::vector<BufferVertex> vertices;
	std::vector<GLuint> indecis;
	std::vector<BufferTexture> bufTex;
	std::vector<Sprite*>::iterator sIt;
	//Gets all sprites with same texture
	for(it = _sprites.begin(); it != _sprites.end(); it++)
	{
		// TODO: needs to bind texture here
		//it->first->bind();
		//Should check for changes before batching
		batchSprites(&it->second);
		for(sIt = it->second.begin(); sIt != it->second.end(); sIt++)
		{
			sprt = *sIt;
			if(sprt->_shdr != shdr)
			{
				shdr = sprt->_shdr;
				//shdr.use() //TODO: Needs to call shader use once implemented
			}
			//returns vec3[4]
			glm::vec3 * points = sprt->getVertices();
			glm::vec2 texBounds;//TODO: = sprt->getTexBounds();
			glm::vec4 color = sprt->Color.getAsOGLVec();
			for(int i = 0; i < 4; i++)
			{
				BufferVertex vertice;
				vertice.Position = points[i];
				vertice.Normal = glm::vec3(0, 0, 0);
				vertice.TexCoords = texBounds;
				vertice.Color = glm::vec3(color.r,color.g,color.b);
				vertices.push_back(vertice);
			}
			indecis.push_back(0);
			indecis.push_back(1);
			indecis.push_back(3);

			indecis.push_back(1);
			indecis.push_back(2);
			indecis.push_back(3);

			_bfr->addBufferData(vertices, indecis,bufTex);
		}
		_bfr->drawBuffer((*shdr));
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

