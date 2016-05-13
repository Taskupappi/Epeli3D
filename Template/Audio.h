#ifndef AUDIO_H
#define AUDIO_H

#include "ResourceBase.h"
#include <ctime>

class Audio
	: public ResourceBase
{
public:
	friend class AudioManager;
	Audio(Mix_Chunk* sound) : ResourceBase(resourcefilepath, nullptr)
	{
		_sound = sound;

		/* Chunks are converted to audio device format... */
		if (!Mix_QuerySpec(&freq, &fmt, &channels))
			printf("Audio error: Mix_OpenAudio never called!\n"); /* never called Mix_OpenAudio()?! */

		/* bytes / samplesize == sample points */
		points = (_sound->alen / ((fmt & 0xFF) / 8));

		/* sample points / channels == sample frames */
		frames = (points / channels);
	}
	~Audio(){};
	/*Play sound effect.
	Set channel to -1
	Set loops to -1 for continuous looping,
	0 plays the sound once.*/
	void playSound(int channel, int loops)
	{
		int isPlaying = Mix_Playing(channel);
		if (isPlaying == 1)
			printf("Sound is already playing! \n\n");

		else if (isPlaying == 0)
		{
			soundIsPlaying = false;

			printf("Playing sound!\n\n");
			Mix_PlayChannel(channel, _sound, loops);
			soundIsPlaying = true;
			if (Mix_GetError())
				printf("Audio error: %s\n", Mix_GetError());
		}
	}
	/*Play sound effect.
	Default channel,
	does not loop.*/
	void playSound()
	{
		int isPlaying = Mix_Playing(-1);

		if (isPlaying != 0)
			printf("Sound is already playing! \n\n");

		else if (isPlaying == 0)
		{
			soundIsPlaying = false;

			printf("Playing sound!\n\n");
			Mix_PlayChannel(-1, _sound, 0);
			soundIsPlaying = true;
			if (Mix_GetError())
				printf("Audio error: %s\n", Mix_GetError());
		}
	}
	/*Set volume for sound.
	Volume range 0-128.*/
	void setVolume(int volume)
	{
		Mix_VolumeChunk(_sound, volume);
		printf_s("Volume: %d\n", volume);
		if (Mix_GetError())
			printf("Audio error: %s\n", Mix_GetError());
	}
	/*Set the position of the sound effect in relation to the listener.
	Angle is an integer from 0 to 360, where 0 is due north. Rotates cockwise.
	Distance is an integer from 0 to 255, where 255 is the furthest away from the listener.*/
	void setSoundDirection(int channel, Sint16 angle, Uint8 distance)
	{
		Mix_SetPosition(channel, angle, distance);
		printf_s("Channel: %d\n", channel);
		printf_s("Angle: %d\n", angle);
		printf_s("Distance: %d\n", distance);
		if (Mix_GetError())
			printf("Audio error: %s\n",Mix_GetError());
	}
	// Returns time length of sound effect in milliseconds
	Uint32 getLength()
	{
		/* (sample frames * 1000) / frequency == play length in ms */
		return ((frames * 1000) / freq);
	}
	// Tells you if sound is playing or not
	bool isPlaying(){ return soundIsPlaying; }
private:
	Audio &operator=(Audio &audio)
	{
		if (this == &audio)
			return *this;
	}

	Mix_Chunk* _sound;
	bool soundIsPlaying = false;
	Uint32 points = 0;
	Uint32 frames = 0;
	int freq = 0;
	Uint16 fmt = 0;
	int channels = 0;
protected:

};

#endif