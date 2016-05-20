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
		_musicIsPlaying = false;
		_paused = false;
		_isDisabled = false;
	}
	~Music(){ Mix_FreeMusic(_music); };
	/*Play music.
	Give number of loops or -1 for continuous looping.
	To play only once leave parameter list empty.
	.*/
	void playMusic(int loops)
	{
		if (_isDisabled)
		{
			printf("Music error: audio is disabled!\n");
		}
		else
		{
			int isPlaying = Mix_PlayingMusic();
			if (isPlaying == 1)
				printf("Music is already playing!\n\n");

			else if (isPlaying == 0)
			{
				_musicIsPlaying = false;

				printf("Playing music!\n\n");
				Mix_PlayMusic(_music, loops);
				_musicIsPlaying = true;
				if (Mix_GetError())
					printf("Music error: %s\n", Mix_GetError());
			}
		}	
	}
	/*Play music once.
	Give number of loops to play music a number of times
	or -1 for continuous looping*/
	void playMusic()
	{
		if (_isDisabled)
		{
			printf("Music error: audio is disabled!\n");
		}
		else
		{
			int isPlaying = Mix_PlayingMusic();
			if (isPlaying == 1)
				printf("Music is already playing!\n\n");

			else if (isPlaying == 0)
			{
				_musicIsPlaying = false;

				printf("Playing music!\n\n");
				Mix_PlayMusic(_music, 0);
				_musicIsPlaying = true;
				if (Mix_GetError())
					printf("Music error: %s\n", Mix_GetError());
			}
		}
	}
	// Stop currently playing music
	void stopMusic()
	{
		Mix_HaltMusic();
		_musicIsPlaying = false;
		printf("Music stopped!\n\n");
		
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
		if (!_isDisabled)
		{
			// Pause
			if (input == 1)
			{
				if (_musicIsPlaying && _paused == false)
				{
					Mix_PauseMusic();
					_musicIsPlaying = false;
					printf("Music paused!\n\n");
					_paused = true;
				}
				else
					printf("No music playing!\n\n");
			}
			// Resume
			else if (input == 0)
			{
				if (!_musicIsPlaying && _paused == true)
				{
					_paused = false;
					Mix_ResumeMusic();
					_musicIsPlaying = true;
					printf("Music resumed!\n\n");
				}
				else if (_musicIsPlaying)
					printf("Music is already playing!\n\n");
				else if (!_paused)
					printf("Music is not paused!\n\n");
			}
			else
				printf("Music error: invalid input! Give 1 to pause and 0 to resume playing music.\n\n");
		}
		else
			printf("Music error: audio is disabled!\n");
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
		_musicIsPlaying = false;
	}
	/*Fade in and play music given number of times
	Fade in time is in milliseconds
	Fade effect applies only to the first loop
	*/
	void fadeInMusic(int fadeInTime, int loops)
	{
		if (_isDisabled)
		{
			printf("Music error: audio is disabled!\n");
		}
		else
		{
			if (!_musicIsPlaying)
			{
				if (Mix_FadeInMusic(_music, loops, fadeInTime) == -1)
				{
					printf("Mix_FadeInMusic: %s\n", Mix_GetError());
				}
				else
				{
					printf("Playing music with fade in effect!\n\n");
					_musicIsPlaying = true;
				}
			}
			else
				printf("Music is already playing!\n\n");
		}
		
	}

	// Tells you if sound is playing or not
	bool isPlaying(){ return _musicIsPlaying; }
	void setIsDisabled(bool state){ _isDisabled = state; }

private:
	Music &operator=(Music &Music)
	{
		if (this == &Music)
			return *this;
	}
	Mix_Music* _music;
	bool _musicIsPlaying;
	bool _paused;
	bool _isDisabled;
	Uint32 points = 0;
	Uint32 frames = 0;
	int freq = 0;
	Uint16 fmt = 0;
	int channels = 0;
protected:

};

#endif