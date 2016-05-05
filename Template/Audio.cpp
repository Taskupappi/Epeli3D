#include "Audio.h"

void Audio::playSound(int loops)
{
	Mix_PlayMusic(_sound, loops);
}

void Audio::setVolume()
{

}