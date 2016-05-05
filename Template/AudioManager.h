#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "Resources.h"
#include "ResourceBase.h"

class Audio;

class AudioManager :
	public ResourceBase
{
	friend class Resources;
public:
	AudioManager(Resources* res) : ResourceBase(resourcefilepath, nullptr)
	{
		_res = res;
	}
	~AudioManager(){}

	Audio * createSound(const std::string& resourcefilepath);

private:
	Resources* _res;
	Audio* _audio;
};

#endif