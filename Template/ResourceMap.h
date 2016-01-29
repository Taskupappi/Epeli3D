#ifndef RESOURCEMAP_H
#define RESOURCEMAP_H
#include "Core.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

template <class T>
class ResourceMap
{
public:
	ResourceMap()
	{
		duplicates = -1;			// undetermined state
		//ResourceManager = NULL;		// no resource manager assigned
	}

	~ResourceMap()
	{
		clearElements();		// remove elements if unique
	}

	//////////////////////////////////////
	// adds a new element

	T* addElement(const std::string &resourceName, const std::string &fileName, void *args = 0)
	{
		if (ResourceManager == NULL)printf_s("Error: DataBase cannot be NULL (5)");
		if (fileName.empty())printf_s("%s : filename cannot be Null", name.c_str());
		if (resourceName.empty())printf_s("%s : resourcename cannot be null", name.c_str());

		// look in the hashmap to see if the resource is already loaded

		std::unordered_map<std::string, T* >::iterator it = Map.find(resourceName);

		if (it == Map.end())
		{
			// if duplicates flag is set to truem duplicated mapped values are allowed
			// if duplicates flag is set to false, duplicates won't be allowed

			if (isValNonUnique(fileName))
			{
				T* resource = ResourceManager->Load(fileName, args);
				// allocate new resource using the raii paradigm
				Map.insert(std::pair<std::string, T*>(resourceName, resource));

				return resource;
			}
			else
			{
				// if we get here and duplicates flag is set to false
				// the filename is duplicated

				printf_s("Error: filename %s must be unique\n", fileName.c_str());
			}
			// if we get here means that resource name is duplicated

			printf_s("Error: Resource name %s must be unique\n", resourceName.c_str());

			return nullptr;
		}
	}

	////////////////////////////////////////
	// delete element using resourceName

	bool removeElement(const std::string &resourceName)
	{
		if (ResourceManager == NULL)printf_s("Error: DataBase cannot be NULL (4)");
		if (resourceName.empty())printf_s("Error: %s: resourceName cannot be NULL", name.c_str());

		// search for item

		std::unordered_map<std::string, T* >::iterator it = Map.find(resourceName);

		// delete element, reference count will be decreased

		if (it != Map.end())
		{
			// save resource name

			std::string fileName = (*it).second->getFileName();

			// erase from this map

			Map.erase(it);

			// check if it is unique and erase it eventually

			ResourceManager->Unload(fileName);

			return true;
		}
		// if we get here, node couldn't be found, exit with an error

		printf_s("%s : couldn't delete %s\n", name.c_str(), resourceName.c_str());
		return false;
	}

	///////////////////////////////////////////////////////
	// clear all the elements from map

	void clearElements()
	{
		std::unordered_map<std::string, T* >::iterator it = Map.begin();
		// walk through the map

		while (it != Map.end())
		{
			// save resource name

			std::string fileName = (*it).second->getFileName();

			// erase from this map

			it = Map.erase(it);

			// check if it is unique and erase it eventually

			ResourceManager->Unload(fileName);
		}
	}

	//////////////////////////////////////////
	// dumps database content to a string

	std::string dump()
	{
		if (ResourceManager == NULL)

			printf_s("Dumping database %s\n\n", name.c_str());
		std::string str = 0;

		for (std::unordered_map<std::string, T*>::iterator it = Map.begin(); it != Map.end(); it++;)
		{
			str += sprintf("resourceName: %s, %s\n",
				(*it).first.c_str(),
				(*it).second->getFileName().c_str());
		}
		return str;
	}
	/////////////////////////////////////////
	// get array name

	const std::string &getName() const{ return name; }
	const int size() const { return Map.size(); }

	/////////////////////////////////////////
	// get const reference to resource manager

	const ResourceManager<T> *getResourceManager(){ return ResourceManager; }

	/////////////////////////////////////////
	// get element using resourceName

	T *getElement(const std::string &resourceName)
	{
		if (ResourceManager == NULL)printf_s("DataBase cannot be NULL (2)");
		if (resourceName.empty())printf_s("%s : resourceName cannot be null", name.c_str());

		std::unordered_map<std::string, T*>::iterator it;

		// searcf for item
		it = Map.find(resourceName);
		//return pointer to element
		if (!= Map.end())
			return it->second;

		// if we get here, node couldn't be found
		printf_s("Error: %s : couldn't find %s", name.c_str(), resourceName.c_str());

		// this point is never reached in case of failure

		return nullptr;
	}
	/////////////////////////////////////
	// setters

	void allowDuplicates(){ duplicates = true; }
	void disallowDuplicates(){ duplicates = false; }

	////////////////////////////////////
	// initialize resource mapper

	void initMapper(const std::string &name, ResourceManager<T> *resourceManager,
		bool duplicates)
	{
		if (resourceManager == NULL) printf_s("DataBase cannot be NULL (1)");
		if (name.empty())printf_s("Array name cannot be null");
	}

private:
	//////////////////////////////
	// find the requested value from the map

	bool isValNonUnique(const std::string &fileName)
	{
		// if duplicates are allowed , then return alwasy true

		if (duplicates) return true;

		// else , check if element by value is already present
		// if it is found, then rturn treu, else exit with false

		std::unordered_map<std::string, T*>::iterator it = Map.begin();

		while (it != Map.end())
		{
			if ((it->second->getFileName() == fileName)) return false;
			++it;
		}
		return true;
	}

	///////////////////////////////////////////
	// private data

	std::string name;
	int duplicates;
	ResourceManager<T>*ResourceManager;			// attached resource manager
	std::unordered_map<std::string, T* >Map;	//resource mapper
};

#endif