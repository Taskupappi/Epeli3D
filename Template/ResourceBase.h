#ifndef RESOURCEBASE_H
#define RESOURCEBASE_H
#include "Core.h"
#include <iostream>

class ResourceBase
{
	template < class T > friend class ResourceManager;

public:
	ResourceBase(const std::string& fileName, void *args)
	{
		// exit with an error if filename is empty

		if (fileName.empty())
			printf_s("Error: empty filename");

		references = 0;
	}

	virtual	~ResourceBase(){}

	const std::string &getFileName() const
	{
		return fileName;
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
	const std::string fileName;
};

#endif