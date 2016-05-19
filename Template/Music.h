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
			printf("Music error: Mix_OpenAudio never called!\n");
		/* never called Mix_OpenMusic()?
		no Music device active?*/

	}
	~Music(){};
	/*Play music.
	Give number of loops or -1 for continuous looping.
	To play only once leave parameter list empty.
	.*/
	void playMusic(int loops)
	{
		int isPlaying = Mix_PlayingMusic();
		if (isPlaying == 1)
			printf("Music is already playing!\n\n");

		else if (isPlaying == 0)
		{
			musicIsPlaying = false;

			printf("Playing music!\n\n");
			Mix_PlayMusic(_music, loops);
			musicIsPlaying = true;
			if (Mix_GetError())
				printf("Music error: %s\n", Mix_GetError());
		}
	}
	/*Play music once.
	Give number of loops to play music a number of times
	or -1 for continuous looping*/
	void playMusic()
	{
		int isPlaying = Mix_PlayingMusic();
		if (isPlaying == 1)
			printf("Music is already playing!\n\n");

		else if (isPlaying == 0)
		{
			musicIsPlaying = false;

			printf("Playing sound!\n\n");
			Mix_PlayMusic(_music, 0);
			musicIsPlaying = true;
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
	/*Pause or resume playing music.
	Give 1 to pause or 0 to resume playing.
	*/
	void pauseMusic(int input)
	{
		// Pause
		if (input == 1)
		{
			if (musicIsPlaying && paused == false)
			{
				Mix_PauseMusic();
				musicIsPlaying = false;
				printf("Music paused!\n\n");
				paused = true;
			}
			else
				printf("No music playing!\n\n");
		}
		// Resume
		else if (input == 0)
		{
			if (!musicIsPlaying && paused == true)
			{
				paused = false;
				Mix_ResumeMusic();
				musicIsPlaying = true;
				printf("Music resumed!\n\n");
			}
			else if (musicIsPlaying)
				printf("Music is already playing!\n\n");
			else if (!paused)
				printf("Music is not paused!\n\n");
		}
		else
			printf("Music error: invalid input! Give 1 to pause and 0 to resume playing music.\n\n");
	}
	/*Fade out and stop playing music
	Fade out time is in milliseconds
	*/
	void fadeOutMusic(int fadeOutTime)
	{
		while (!Mix_FadeOutMusic(fadeOutTime) && Mix_PlayingMusic())
		{
			// Wait for fades to complete
			SDL_Delay(100);
		}
		musicIsPlaying = false;
	}
	/*Fade in and play music given number of times
	Fade in time is in milliseconds
	Fade effect applies only to the first loop
	*/
	void fadeInMusic(int fadeInTime, int loops)
	{
		if (!musicIsPlaying)
		{
			if (Mix_FadeInMusic(_music, loops, fadeInTime) == -1)
			{
				printf("Mix_FadeInMusic: %s\n", Mix_GetError());
			}
			else
				musicIsPlaying = true;
		}
		else
			printf("Music is already playing!\n\n");
	}


	// Tells you if sound is playing or not
	bool isPlaying(){ return musicIsPlaying; }

private:
	Music &operator=(Music &Music)
	{
		if (this == &Music)
			return *this;
	}

	Mix_Music* _music;
	bool musicIsPlaying = false;
	bool paused = false;
	Uint32 points = 0;
	Uint32 frames = 0;
	int freq = 0;
	Uint16 fmt = 0;
	int channels = 0;
protected:

};

#endif