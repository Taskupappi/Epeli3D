#ifndef TESTIFOO_H
#define TESTIFOO_H

#include "ResourceBase.h"

class TestiFoo :
	public ResourceBase
{
public:
	// this constructor must be present
	TestiFoo(const std::string &resourcefilename, void *args) : ResourceBase(resourcefilename, args){}

	// regular base constructor and destructor
	//TestiFoo(){}
	~TestiFoo(){}
	
private:
	////////////////////////////////////
	// copy constructor and overload operator are private
	// no copies allowed since classes are referenced

	TestiFoo(const TestiFoo &foo) : ResourceBase(foo){}

	TestiFoo &operator =(TestiFoo &foo)
	{
		if (this == &foo)
			return *this;
		return *this;
	}
};

#endif