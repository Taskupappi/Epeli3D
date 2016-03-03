#ifndef AUDIO_H
#define AUDIO_H

#include "Core.h"
#include "ResourceBase.h"

class Audio
	: public ResourceBase
{
public:
	Audio(const std::string &resourcefilepath, Mix_Music* sound) : ResourceBase(resourcefilepath, sound)
	{
	}
	~Audio(){};


private:
	Audio &operator=(Audio &audio)
	{
		if (this == &audio)
			return *this;
	}

	Mix_Music* sound = 0;
};

#endif