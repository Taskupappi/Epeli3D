#ifndef RESOURCEBASE_H
#define RESOURCEBASE_H
#include "ResourceManager.h"
#include <iostream>

class ResourceBase
{
	template < class T > friend class ResourceManager;

public:
	ResourceBase(const std::string& resourcefilename, void *args) : resourcefilename(resourcefilename)
	{
		// exit with an error if filename is empty

		if (resourcefilename.empty())
			printf_s("Error: empty filename\n");

		references = 0;
	}

	virtual	~ResourceBase(){}

	const std::string &getResourceFileName() const
	{
		return resourcefilename;
	}

	const int getReferenceCount() const
	{
		return references;
	}

private:
	int references;

	void incReferences() { references++; }
	void decReferences() { references--; }

protected:
	// copy constructor and = operator
	ResourceBase(const ResourceBase& object){}
	ResourceBase& operator=(const ResourceBase& object){ return *this; }

	// filename
	const std::string resourcefilename;
};

#endif