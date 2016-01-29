#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ResourceBase.h"

class GameObject :
	public ResourceBase
{
	////////////////////////////////////
	// copy constructor and overload operator are private
	// no copies allowed since classes are referenced

	GameObject(const GameObject &object) : ResourceBase(object){}

	GameObject &operator=(GameObject &object)
	{
		if (this == &object)
			return *this;
	}

public:
	// this constructor must be present
	GameObject(const std::string &resourceFileName, void *args) : ResourceBase(resourceFileName, args){}

	// regular base constructor and destructor
	//GameObject(){}
	~GameObject(){}
};

#endif