#include "LightSource.h"


LightSource::LightSource(std::string type,float intensity, glm::vec3 rgb)
{
	_type = type;
	_intensity = intensity;
	_rgb.x = rgb.x / 255; // punainen
	_rgb.y = rgb.y / 255; // vihreä
	_rgb.z = rgb.z / 255; // sininen
	calculate();
	_radius = { 1.0, 1.0, 1.0 };
	_position = { 0, 0, 0 };

}

LightSource::~LightSource()
{
}

void LightSource::setIntensity(float intensity)
{
	_intensity = intensity;
}

void LightSource::setRadius(glm::vec3 radius)
{
	_radius = radius;
}

void LightSource::setPosition(glm::vec3 position)
{
	_position = position;
}

void LightSource::calculate()
{
	float colorMax = 0;
	float colorMin = _rgb.x;
	
	for (int i = 0; i < 3; i++)
	{
		if (_rgb[i]>colorMax)
		{
			colorMax = _rgb[i];
		}

		if (_rgb[i] < colorMin)
		{
			colorMin = _rgb[i];
		}
	}

	float colorDelta = colorMax - colorMin;

	// sävyn laskenta
	if (colorMax == _rgb.x)
	{
		_hue = 60 * (fmod((_rgb.y - _rgb.z) / colorDelta, 6));
	}
	else if (colorMax == _rgb.y)
	{
		_hue = 60 * (((_rgb.z - _rgb.x) / colorDelta) + 2);
	}
	else
	{
		_hue = 60 * (((_rgb.x - _rgb.y) / colorDelta) + 4);
	}

	// valoisuuden laskenta
	_lightness = (colorMax + colorMin) / 2;

	// saturaation laskenta
	_saturation = colorDelta / (1 - fabs(2 * _lightness - 1));
}

void LightSource::move(glm::vec3 movement)
{
	_position += movement;
}


