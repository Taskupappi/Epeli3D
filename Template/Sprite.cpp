#include "Sprite.h"
using namespace graphics;
/* // No rotation
glm::vec3 * Sprite::getVertices()
{
	glm::vec3 pos = getPosition();
	glm::vec3 corners[4] = {pos,pos,pos,pos};
	//Calculate corner points here
	corners[1].x += _width;
	corners[2].y += _height;
	corners[3].x += _width;
	corners[3].y += _height;
	
	return corners;
}
*/

glm::vec3 * Sprite::getVertices()
{
	glm::vec4 pos = glm::vec4(getPosition(), 0.0f);
	pos.z = 0.0f;
	glm::vec4 corners[4] = { pos, pos, pos, pos };
	//Calculate corner points here
	corners[0].y += _height;
	corners[1].x += _width;
	corners[1].y += _height;

	//corners[2].y += _height;
	corners[3].x += _width;
	//corners[3].y += _height;

	//TODO: Need to debug this:
	corners[0] = getTransfMat() * corners[0];
	corners[1] = getTransfMat() * corners[1];
	corners[2] = getTransfMat() * corners[2];
	corners[3] = getTransfMat() * corners[3];

	_positions[0] = glm::vec3(corners[0]);
	_positions[1] = glm::vec3(corners[1]);
	_positions[2] = glm::vec3(corners[2]);
	_positions[3] = glm::vec3(corners[3]);

	return _positions;
}

glm::vec2 * Sprite::getTexBounds()
{
	//TODO: Calculate proper bounds and spritesheets
	//As is only draws full texture
	glm::vec2 retVal[2] = { glm::vec2(0, 0), glm::vec2(1.0, 1.0) };
	return retVal;
}
