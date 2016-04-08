#ifndef Resources_H
#define Resources_H

#include "ResourceBase.h"
//#include "Core.h"
#include "Texture.h"
#include "ImageResource.h"
#include "Audio.h"
#include "Text.h"
#include <unordered_map>
#include <iostream>
#include <fstream>


class Resources :
	public ResourceBase
{
public:
	// this constructor must be present
	Resources(const std::string &resourcefilepath, void *args) : ResourceBase(resourcefilepath, args){}

	// regular base constructor and destructor
	//Resources(){}
	~Resources(){}

	template <class T>
	T* loadFile(const std::string &resourcefilepath)
	{
		// T * loadedResource = nullptr;
		ResourceBase * loadedResource = NULL;
		bool isLoaded = NULL;

		size_t pos = resourcefilepath.find_last_of("/");
		if (pos != std::string::npos)
			FileName = resourcefilepath.substr(pos + 1);

		// Init TEXTURE manager and map, load file to map
		if (typeid(T).hash_code() == typeid(SDL_Surface).hash_code())
		{
			if (!texturesInit)
			{
				imageM.initResourceManager("ImageDataBase");
				imageMap.initMapper("ImageMap", &imageM, true);
				texturesInit = true;
			}
			printf_s("Checking if file has already been loaded\n");
			if (imageMap.getElement(FileName))
				isLoaded = true;
			else
				isLoaded = false;

			// if file has not been loaded, load it
			if (!isLoaded)
			{
				image = IMG_Load((resourcefilepath).c_str());

				if (!image)
					printf("IMG_Load: %s\n", IMG_GetError());
					
				// TODO: KEKSI MITEN IMAGET MAPPIIN LAITAN
				loadedResource = new ImageResource(image);
				imageMap.addElement(FileName, resourcefilepath, loadedResource);
				
				// HAX???
				return (T*)image;
			}
			// if file has already been loaded, skip loading
			else if (isLoaded)
			{
				T * tex = (T*)imageMap.getElement(FileName);
				printf_s("File %s already loaded\n", FileName.c_str());
				printf_s("Increasing reference count for file: %s\n\n", FileName.c_str());
				tex->incReferences();
				return tex;
			}
		}

		// Init AUDIO manager and map, load file to map
		else if (typeid(T).hash_code() == typeid(Audio).hash_code())
		{
			if (!audioInit)
			{
				audioM.initResourceManager("AudioDataBase");
				audioMap.initMapper("AudioMap", &audioM, true);
				audioInit = true;
			}
			printf_s("Checking if file has already been loaded\n");
			if (audioMap.getElement(FileName))
				isLoaded = true;
			else
				isLoaded = false;

			// if file has not been loaded, load it
			if (!isLoaded)
			{
				sound = Mix_LoadMUS((resourcefilepath).c_str());
				if (!sound)
					printf_s("Mix_LoadMus: %s\n", Mix_GetError);

				loadedResource = new Audio(sound);
				
				audioMap.addElement(FileName, resourcefilepath, loadedResource);
				//return (T*)sound;
			}
			// if file has already been loaded, skip loading
			else if (isLoaded)
			{
				T * audio = (T*)audioMap.getElement(FileName);
				printf_s("File %s already loaded\n", FileName.c_str());
				printf_s("Increasing reference count for file: %s\n\n", FileName.c_str());
				audio->incReferences();
				return audio;
			}									
		}

		// Init STRING manager and map, load file to map
		else if (typeid(T).hash_code() == typeid(Text).hash_code())
		{
			if (!txtInit)
			{
				txtM.initResourceManager("TextDataBase");
				txtMap.initMapper("TextMap", &txtM, true);
				txtInit = true;
			}
			printf_s("Checking if file has already been loaded\n");
			if (txtMap.getElement(FileName))
				isLoaded = true;
			else
				isLoaded = false;

			// if file has not been loaded, load it
			if (!isLoaded)
			{
				txt = SDL_RWFromFile(resourcefilepath.c_str(), "r"); // read only
				fileSize = SDL_RWsize(txt);

				if (txt != NULL)
				{
					char *content = new char[fileSize];
					content[fileSize] = '\0';

					txt->read(txt, content, fileSize, 1);
					txt->close(txt);

					//txtcontent = content;
					std::cout << txtcontent << std::endl << std::endl;

					content[1];
				}
				if (txt == NULL) {
					fprintf(stderr, "Error: couldn't open %s\n\n", FileName.c_str());
				}

				loadedResource = new Text(txtcontent);
				
				txtMap.addElement(FileName, resourcefilepath, loadedResource);

				//return (T*)txtcontent;
			}
			// if file has already been loaded, skip loading
			else if (isLoaded)
			{
				T * text = (T*)txtMap.getElement(FileName);
				printf_s("File %s already loaded\n", FileName.c_str());
				printf_s("Increasing reference count for file: %s\n\n", FileName.c_str());
				text->incReferences();
				return text;
			}
		}
	}
private:

	////////////////////////////////////
	// copy constructor and overload operator are private
	// no copies allowed since classes are referenced

	Resources(const Resources &foo) : ResourceBase(foo){}

	Resources &operator =(Resources &foo)
	{
		if (this == &foo)
			return *this;
		return *this;
	}
	SDL_Surface *image = NULL;		// for all textures
	GLuint texture = NULL;

	ResourceManager<ResourceBase>imageM;
	ResourceMap<ResourceBase>imageMap;

	Mix_Music *sound = NULL;		// for all audio files
	ResourceManager<ResourceBase>audioM;
	ResourceMap<ResourceBase>audioMap;

	SDL_RWops *txt = NULL;		// for shaders/text files
	std::string txtcontent;
	ResourceManager<ResourceBase>txtM;
	ResourceMap<ResourceBase>txtMap;

	bool texturesInit = false;
	bool audioInit = false;
	bool txtInit = false;

	std::string FileName;
	int fileSize = 0;
};

#endif