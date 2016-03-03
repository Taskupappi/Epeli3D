#ifndef TIME_H
#define	TIME_H

#include "SDL.h"

class Time
{
public:
	Time();
	~Time();

	void reset()
	{
		pastTicks = 0;
	}
	
	void start()
	{
		started = true;
		paused = false;

		pastTicks = SDL_GetTicks();

		pausedTicks = 0;
	}

	void stop()
	{
		started = false;
		paused = false;

		pastTicks = 0;
		pausedTicks = 0;
	}

	void pause()
	{
		if (started && !paused)
		{
			paused = true;

			pausedTicks = SDL_GetTicks() - pastTicks;
			pastTicks = 0;
		}
	}

	void resume()
	{
		if (started && paused)
		{
			paused = false;

			pastTicks = SDL_GetTicks() - pausedTicks;

			pausedTicks = 0;
		}
	}

	void getElapsedTime()
	{
		if (paused == true)
		{
			elapsedTime = 0;
		}
	}

private:
	Uint32 pastTicks, pausedTicks;
	double pausedTime, elapsedTime;
	bool started, paused;

};


#endif