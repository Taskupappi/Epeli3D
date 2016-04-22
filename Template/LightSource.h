#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>
#include <iostream>
#include <cmath>

class LightSource
{
public:
	LightSource(std::string type, float intensity, glm::vec3 rgb);
	~LightSource();

	void setIntensity(float i); // lighting radius
	void setRadius(glm::vec3);
	void setPosition(glm::vec3);
	void setType();

	float getIntensity(){ return _intensity; }
	glm::vec3 getDirection(){ return _radius; }
	glm::vec3 getPosition(){ return _position; }
	std::string getType(){ return _type; }

	void move(glm::vec3);
	void rotate();

	void render();

private:
	float _intensity;
	float _hue;
	float _saturation;
	float _lightness;

	glm::vec2 _direction;
	glm::vec3 _radius;
	glm::vec3 _position;
	glm::vec3 _rgb; // x = punainen, y = vihreä, z = sininen
	std::string _type;

	void calculate();
};
#endif

