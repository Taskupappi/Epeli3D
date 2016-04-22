#ifndef AUDIO_H
#define AUDIO_H

#include "Core.h"
#include "ResourceBase.h"

class Audio
	: public ResourceBase
{
public:
	Audio(Mix_Music* sound) : ResourceBase(resourcefilepath, nullptr)
	{
		_sound = sound;
	}
	~Audio(){};
	
private:
	Audio &operator=(Audio &audio)
	{
		if (this == &audio)
			return *this;
	}

	Mix_Music* _sound;
};

#endif