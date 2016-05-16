#ifndef MUSIC_H
#define MUSIC_H

#include "ResourceBase.h"
#include <ctime>

class Music
	: public ResourceBase
{
public:
	friend class AudioManager;
	/* Class for music
	Supports a single channel
	Supported file types: WAV, MP3, OGG, FLAC and MOD files*/
	Music(Mix_Music* music) : ResourceBase(resourcefilepath, nullptr)
	{
		_music = music;

		/* Chunks are converted to Music device format... */
		if (!Mix_QuerySpec(&freq, &fmt, &channels))
			printf("Music error: Mix_OpenMusic never called!\n");
		/* never called Mix_OpenMusic()?
		no Music device active?*/

	}
	~Music(){};
	/*Play music.
	Set loops to -1 for continuous looping,
	0 plays the sound once.*/
	void playMusic(int loops)
	{
		int isPlaying = Mix_PlayingMusic();
		if (isPlaying == 1)
			printf("Sound is already playing! \n\n");

		else if (isPlaying == 0)
		{
			soundIsPlaying = false;

			printf("Playing music!\n\n");
			Mix_PlayMusic(_music, loops);
			soundIsPlaying = true;
			if (Mix_GetError())
				printf("Music error: %s\n", Mix_GetError());
		}
	}
	/*Play music.
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
			Mix_PlayMusic(_music, 0);
			soundIsPlaying = true;
			if (Mix_GetError())
				printf("Music error: %s\n", Mix_GetError());
		}
	}
	/*Set volume for sound.
	Volume range 0-128.*/
	void setVolume(int volume)
	{
		Mix_VolumeMusic(volume);
		printf_s("Volume: %d\n", volume);
		if (Mix_GetError())
			printf("Music error: %s\n", Mix_GetError());
	}


	// Tells you if sound is playing or not
	bool isPlaying(){ return soundIsPlaying; }

private:
	Music &operator=(Music &Music)
	{
		if (this == &Music)
			return *this;
	}

	Mix_Music* _music;
	bool soundIsPlaying = false;
	Uint32 points = 0;
	Uint32 frames = 0;
	int freq = 0;
	Uint16 fmt = 0;
	int channels = 0;
protected:

};

#endif