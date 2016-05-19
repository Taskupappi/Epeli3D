#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "Core.h"
#include "ResourceBase.h"

class SoundFX;
class Music;

class AudioManager :
	public ResourceBase
{
	friend class Resources;
public:
	AudioManager(Resources* res) : ResourceBase(resourcefilepath, nullptr)
	{
		_res = res;
		_isInitialised = false;
	}
	~AudioManager(){}
	SoundFX * createSoundEffect(const std::string& resourcefilepath);
	Music * createMusic(const std::string& resourcefilepath);

	void setIsInitialised(bool state);
	bool getIsInitialised();
private:
	Resources* _res;
	SoundFX* _sound;
	Music* _music;
	bool _isInitialised;
};

#endif