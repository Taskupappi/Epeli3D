#ifndef TEXT_H
#define TEXT_H

#include "Core.h"
#include "ResourceBase.h"
#include <string>

class Text
	: public ResourceBase
{
public:
	Text(const std::string &resourcefilepath, SDL_RWops* txt) : ResourceBase(resourcefilepath, txt)
	{
	}
	~Text(){};


private:
	Text &operator=(Text &text)
	{
		if (this == &text)
			return *this;
	}

	SDL_RWops* txt = 0;
};

#endif