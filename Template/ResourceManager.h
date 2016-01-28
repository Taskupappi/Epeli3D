#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <iostream>
#include <typeinfo>
#include <vector>
#include <fstream>
#include <map>


template <class T>
class ResourceManager
{
	ResourceManager()
	{
	}
	
	~ResourceManager()
	{
		ReleaseAll();
	}

	public:
		//-----
		//Add an asset to the database
		T* Load(const std::string &filename, void *args)
		{
			//check if filename is not empty
			if (filename.empty())
			{
				//error message
			}

			//normalize filename
			//std::string Filename=CStringFormatter::TrimAndLower( filename );

			//looks in the map to see if the resource is already loaded
			std::unordered_map<std::string, T*>::iterator it = Map.find(FileName);

			if (it != Map.end())
			{
				(*it).second->IncReferences();
				return (*it).second;
			}

			//if we get here the resource must be loaded
			//allocate new resource using the raii paradigm
			//you must supply the class with a proper constructor
			//see header for details

			T *resource = new T(FileName, args);

			//increase references, this sets the references count to 1
			resource->IncReferences();

			//insert into the map
			Map.insert(std::pair<std string, T*>(FileName, resource);

			return resource;
		}

		//-----
		//deleting an item

		bool Unload(const std::string &filename)
		{
			//check if filename is not empty
			if (filename.empty())
			{
				//error message
			}

			//normalize it
			//std::string Filename=CStringFormatter::TrimAndLower( filename );

			//find the item to delete
			std::unordered_map<std::string, T*>::iterator it = Map.find(FileName);

			if (it != Map.end())
			{
				//decrease references
				(*it).second->DecReferences();

				//if item had 0 references, meaning
				//the item isn't more used,
				//delete from main database
				if ((*it).second->GetReferencesCount() == 0)
				{
					delete((*it).second);
					Map.erase(it);
				}

				return true;
			}

			//Error message
			return false;
		}


		//-----
		//get name for database
		const std::string &GetName() const { return Name; }
		const int Size() const { return Map.size; }


	private:
		//data members
		std::unordered_map<std::string, T* > Map;
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