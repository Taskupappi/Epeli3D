#include "AudioManager.h"


Audio * AudioManager::createSound(const std::string &resourcefilepath)
{
	_audio = _res->loadFile<Audio>(resourcefilepath);
	
	return _audio;
}