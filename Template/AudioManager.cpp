#include "AudioManager.h"


SoundFX * AudioManager::createSoundEffect(const std::string &resourcefilepath)
{
	_sound = _res->loadFile<SoundFX>(resourcefilepath);
	
	return _sound;
}