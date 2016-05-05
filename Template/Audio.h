#ifndef AUDIO_H
#define AUDIO_H

#include "ResourceBase.h"
//#include "AudioManager.h"

class Audio
	: public ResourceBase
{
public:
	//friend class AudioManager;
	Audio(Mix_Music* sound) : ResourceBase(resourcefilepath, nullptr)
	{
		_sound = sound;
		loops = 0;
	}
	~Audio(){};
	// Play sound, set loops to -1 for continuous loop
	void playSound(int loops);
	void setVolume();
private:
	Audio &operator=(Audio &audio)
	{
		if (this == &audio)
			return *this;
	}

	Mix_Music* _sound;
	int loops;

protected:

};

#endif