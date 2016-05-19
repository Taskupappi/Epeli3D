#include "AudioManager.h"


SoundFX * AudioManager::createSoundEffect(const std::string &resourcefilepath)
{
	_sound = _res->loadFile<SoundFX>(resourcefilepath);
	
	return _sound;
}

Music * AudioManager::createMusic(const std::string &resourcefilepath)
{
	_music = _res->loadFile<Music>(resourcefilepath);

	return _music;
}

void AudioManager::setIsInitialised(bool state)
{
	_isInitialised = state;
}

bool AudioManager::getIsInitialised()
{
	if (!_isInitialised)
		return true;
	else
		return false;
}