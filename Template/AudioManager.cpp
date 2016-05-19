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