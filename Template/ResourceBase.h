#ifndef RESOURCEBASE_H
#define RESOURCEBASE_H
#include "ResourceManager.h"
#include <iostream>
#include "ResourceMap.h"

class ResourceBase
{
	template < class T > friend class ResourceManager;
	template < class T > friend class ResourceMap;
	friend class Resources;
public:
	ResourceBase(const std::string& resourcefilepath, void *args) : resourcefilepath(resourcefilepath)
	{
		// exit with an error if filename is empty

		/////// NOT NEEDED
		//if (resourcefilepath.empty())
		//	printf_s("Error: empty filename\n");

		size_t pos = resourcefilepath.find_last_of("/");
		if (pos != std::string::npos)
			resourcefilename = resourcefilepath.substr(pos + 1);

		references = 0;
	}

	virtual	~ResourceBase(){}

	const std::string &getResourceFileName()
	{
		//// find "." in string
		//std::string extension = "";
		//size_t pos = resourcefilepath.find_last_of("/");

		//// check if position is valid
		//if (pos != std::string::npos)
		//	extension = resourcefilepath.substr(pos + 1);
		//resourcefilename = extension;
		return resourcefilename;
	}

	const std::string &getResourceFilepath() const
	{
		return resourcefilepath;
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
	const std::string resourcefilepath;
	std::string resourcefilename = "";
};

#endif