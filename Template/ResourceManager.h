#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>


template <class T>
class ResourceManager
{
public:
	ResourceManager()
	{
	}
	
	~ResourceManager()
	{
		ReleaseAll();
	}


		//-----
		//Add an asset to the database
		T* Load(const std::string &filename, void *args)
		{
			//check if filename is not empty
			if (filename.empty())
			{
				printf_s("Load error: filename cannot be empty!\n");
			}

			//normalize filename
			//std::string Filename=CStringFormatter::TrimAndLower( filename );

			//looks in the map to see if the resource is already loaded
			std::unordered_map<std::string, T*>::iterator it;
			it = Map.find(filename);

			if (it != Map.end())
			{
				printf_s("Increasing reference count for file: %s\n", filename.c_str());
				(*it).second->incReferences();
				return (*it).second;
			}

			//if we get here the resource must be loaded
			//allocate new resource using the raii paradigm
			//you must supply the class with a proper constructor
			//see header for details

			T* resource = new T(filename, args);

			//increase references, this sets the references count to 1
			printf_s("First reference of file: %s\n", filename.c_str());
			resource->incReferences();

			//insert into the map
			Map.insert(std::pair<std::string, T*>(filename, resource));

			return resource;
		}

		//-----
		//deleting an item

		bool Unload(const std::string &filename)
		{
			//check if filename is not empty
			if (filename.empty())
			{
				printf_s("Unload error: filename cannot be empty!\n");
			}

			//normalize it
			//std::string Filename=CStringFormatter::TrimAndLower( filename );

			//find the item to delete
			std::unordered_map<std::string, T*>::iterator it = Map.find(filename);

			if (it != Map.end())
			{
				//decrease references
				printf_s("Decreasing reference count for file: %s\n", filename.c_str());
				(*it).second->decReferences();

				//if item had 0 references, meaning
				//the item isn't more used,
				//delete from main database
				if ((*it).second->getReferenceCount() == 0)
				{
					delete((*it).second);
					Map.erase(it);
				}

				return true;
			}

			printf_s("Error: cannot find file: %s\n", filename.c_str());
			return false;
		}

		void initResourceManager(const std::string &name)
		{
			// check if name is not empty
			if (name.empty())
				printf_s("Error: Null name is not allowed\n");
			Name = name;
		}

		//-----
		//get name for database
		const std::string &GetName() const { return Name; }
		const int Size() const { return Map.size(); }


	private:
		//data members
		std::unordered_map<std::string, T*> Map;
		std::string Name;

		//copy constructor and = operator are kept private
		ResourceManager(const ResourceManager&) {};
		ResourceManager &operator = (const ResourceManager&) { return *this; }

		//force removal for each node
		void ReleaseAll()
		{
			std::unordered_map<std::string, T*>::iterator it = Map.begin();

			while (it != Map.end())
			{
				delete (*it).second;
				it = Map.erase(it);
			}
		}

};

//class ResourceManager
//{
//public:
//	ResourceManager(){};
//	~ResourceManager(){};
//	template< typename T>
//	T* loadResourceT(const std::string fileName)
//	{
//		return nullptr;
//		{
//			/*
//			switch (typeid(T).hash_code())
//			{
//			case typeid(Image).hash_code():
//				//Image * img = loadImage(fileName);
//				//return img;
//				return nullptr;
//				break;
//				// case typeid(audio).name():
//			default:
//				break;
//			}
//			*/
//		}
//	}
//	void loadResource(const std::string fileName);
//	void loadImage(const std::string fileName);
//	void load3DModel(const std::string fileName);
//	void loadShader(const std::string fileName);
//	void loadFont(const std::string fileName);
//	void loadSound(const std::string fileName);
//
//private:
//	SDL_Surface *image;
//	Mix_Music *audio;
//	const std::string imageFilePath = "../data/Resource/Images/";
//	const std::string audioFilePath = "../data/Resource/Audio/";
//	const std::string modelFilePath = "../data/Resource/Models/";
//	const std::string shaderFilePath = "../data/Shaders/";
//	const std::string fontFilePath = "../data/Fonts/";
//	const std::string fileName;
//};

#endif