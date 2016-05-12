#ifndef AUDIO_H
#define AUDIO_H

#include "ResourceBase.h"

class Audio
	: public ResourceBase
{
public:
	friend class AudioManager;
	Audio(Mix_Chunk* sound) : ResourceBase(resourcefilepath, nullptr)
	{
		_sound = sound;
	}
	~Audio(){};
	/*Play sound effect.
	Set channel to -1
	Set loops to -1 for continuous looping,
	0 plays the sound once.*/
	void playSound(int channel, int loops)
	{

		printf("Playing sound!\n\n");
		Mix_PlayChannel(channel, _sound, loops);
	}
	/*Set volume for sound.
	Volume range 0-128.*/
	void setVolume(int volume)
	{
		Mix_VolumeChunk(_sound, volume);
		printf_s("Volume: %d\n", volume);
	}
	/*Set the position of the sound in relation to the listener.
	Angle is an integer from 0 to 360, where 0 is due north. Rotates cockwise.
	Distance is an integer from 0 to 255, where 255 is the furthest away from the listener.*/
	void setSoundDirection(int channel, Sint16 angle, Uint8 distance)
	{
		Mix_SetPosition(channel, angle, distance);
		printf_s("Angle: %d\n", angle);
		printf_s("Distance: %d\n", distance);
	}
	
private:
	Audio &operator=(Audio &audio)
	{
		if (this == &audio)
			return *this;
	}

	Mix_Chunk* _sound;
	bool soundIsPlaying = false;
protected:

};

#endif