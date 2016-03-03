#ifndef TEXT_H
#define TEXT_H

#include "Core.h"
#include "ResourceBase.h"

class Text
	: public ResourceBase
{
public:
	Text(const std::string &resourcefilepath, std::string* txt) : ResourceBase(resourcefilepath, txt){};
	~Text(){};


private:
	std::string* txt = 0;
};

#endif