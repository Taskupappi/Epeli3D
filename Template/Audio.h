#ifndef AUDIO_H
#define AUDIO_H

#include "ResourceBase.h"
#include "AudioManager.h"

class Audio
	: public ResourceBase
{
public:
	friend class AudioManager;
	Audio(Mix_Music* sound) : ResourceBase(resourcefilepath, nullptr)
	{
		_sound = sound;
	}
	~Audio(){};
	/*Play sound.
	Set loops to -1 for continuous looping,
	0 plays the sound once.*/
	void playSound(int loops)
	{
		Mix_PlayMusic(_sound, -1);
	}
	/*Set volume for sound.
	Set channel to -1 to set volume for all channels.
	Volume range 0-128.*/
	void setVolume(int channel, int volume)
	{
		Mix_Volume(channel, volume);
		printf_s("Volume: %d", Mix_Volume(-1, -1));
	}
	/*Set the position of the sound in relation to the listener.
	Angle is an integer from 0 to 360, where 0 is due north. Rotates cockwise.
	Distance is an integer from 0 to 255, where 255 is the furthest away from the listener.*/
	void setSoundDirection(int channel, Sint16 angle, Uint8 distance)
	{
		//Mix_SetPosition(channel, angle, distance);
	}
private:
	Audio &operator=(Audio &audio)
	{
		if (this == &audio)
			return *this;
	}

	Mix_Music* _sound;

protected:

};

#endif