#ifndef TEXT_H
#define TEXT_H

#include "Core.h"
#include "ResourceBase.h"
#include <string>

class Text
	: public ResourceBase
{
public:
	Text(std::string txt) : ResourceBase(resourcefilepath, nullptr)
	{
		_txt = txt;
	}
	~Text(){};


private:
	Text &operator=(Text &text)
	{
		if (this == &text)
			return *this;
	}

	std::string _txt;
};

#endif