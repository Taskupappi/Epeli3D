#ifndef SOUNDFX_H
#define SOUNDFX_H

#include "ResourceBase.h"
#include <ctime>

class SoundFX
	: public ResourceBase
{
public:
	friend class AudioManager;
	/* Class for sound effects
	Supports any number of simultaneously playing channels of 16 stereo SoundFX
	Supported file types: WAV, MP3, OGG and MOD files*/
	SoundFX(Mix_Chunk* sound) : ResourceBase(resourcefilepath, nullptr)
	{
		_sound = sound;
		_soundIsPlaying = false;
		_isDisabled = false;
		/* Chunks are converted to SoundFX device format... */
		/* bytes / samplesize == sample points */
		//points = (_sound->alen / ((fmt & 0xFF) / 8));

		///* sample points / channels == sample frames */
		//frames = (points / channels);
	}
	~SoundFX(){ Mix_FreeChunk(_sound); };
	/*Play sound effect.
	Set channel to -1
	Set loops to -1 for continuous looping,
	0 plays the sound once.*/
	void playSound(int channel, int loops)
	{
		if (_isDisabled)
		{
			printf("SoundFX error: audio is disabled!\n");
		}
		else
		{
			int isPlaying = Mix_Playing(channel);
			if (isPlaying == 1)
				printf("Sound is already playing! \n\n");

			else if (isPlaying == 0)
			{
				_soundIsPlaying = false;

				printf("Playing sound!\n\n");
				Mix_PlayChannel(channel, _sound, loops);
				_soundIsPlaying = true;
				if (Mix_GetError())
					printf("SoundFX error: %s\n", Mix_GetError());
			}
		}
	}
	/*Play sound effect.
	Automatically chooses a channel, does not loop.
	Use this if you want to use more than one instance of the same sound at once.*/
	void playSound()
	{
		if (_isDisabled)
		{
			printf("SoundFX error: audio is disabled!\n");
		}
		else
		{
			_soundIsPlaying = false;

			printf("Playing sound!\n\n");
			Mix_PlayChannel(-1, _sound, 0);
			_soundIsPlaying = true;
			if (Mix_GetError())
				printf("SoundFX error: %s\n", Mix_GetError());
		}	
	}
	/*Set volume for sound.
	Volume range 0-128.*/
	void setVolume(int volume)
	{
		if (!_isDisabled)
		{
			Mix_VolumeChunk(_sound, volume);
			printf_s("Volume: %d\n", volume);
			if (Mix_GetError())
				printf("SoundFX error: %s\n", Mix_GetError());
		}
	}
	/*Set the position of the sound effect in relation to the listener.
	Angle is an integer from 0 to 360, where 0 is due north. Rotates cockwise.
	Distance is an integer from 0 to 255, where 255 is the furthest away from the listener.
	Note that maximum distance doesn't mean silence.*/
	void setSoundDirection(int channel, Sint16 angle, Uint8 distance)
	{
		if (!_isDisabled)
		{
			Mix_SetPosition(channel, angle, distance);
			printf_s("Channel: %d\n", channel);
			printf_s("Angle: %d\n", angle);
			printf_s("Distance: %d\n", distance);
			if (Mix_GetError())
				printf("SoundFX error: %s\n", Mix_GetError());
		}
	}
	// Returns time length of sound effect in milliseconds
	//Uint32 getLength()
	//{
	//	/* (sample frames * 1000) / frequency == play length in ms */
	//	return ((frames * 1000) / freq);
	//}
	// Tells you if sound is playing or not
	bool isPlaying(){ return _soundIsPlaying; }
	void setIsDisabled(){ _isDisabled = true; }
private:
	SoundFX &operator=(SoundFX &SoundFX)
	{
		if (this == &SoundFX)
			return *this;
	}
	bool _isDisabled=false;
	Mix_Chunk* _sound;
	bool _soundIsPlaying;
	Uint32 points = 0;
	Uint32 frames = 0;
	int freq = 0;
	Uint16 fmt = 0;
	int channels = 0;
protected:

};

#endif