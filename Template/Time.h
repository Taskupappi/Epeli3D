#ifndef TIME_H
#define	TIME_H

#include "SDL.h"

class Time
{
public:
	Time();
	~Time();

	void reset();
	void start();
	void pause();
	void resume();
	void getElapsedTime();

private:
	bool paused;

};


#endif