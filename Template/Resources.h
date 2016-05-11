#ifndef Resources_H
#define Resources_H

#include "ResourceBase.h"
//#include "Core.h"
#include "ImageResource.h"
#include "Audio.h"
#include "Text.h"
#include <unordered_map>
#include <iostream>
#include <fstream>

class Object3D;
class Mesh;

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
		ResourceBase * loadedResource = nullptr;
		bool isLoaded = NULL;
		std::string FileName;
		size_t pos = resourcefilepath.find_last_of("/");
		if (pos != std::string::npos)
			FileName = resourcefilepath.substr(pos + 1);

		// Init IMAGE manager and map, load file to map
		if (typeid(T).hash_code() == typeid(ImageResource).hash_code())
		{
			if (!texturesInit)
			{
				imageM.initResourceManager("ImageDataBase");
				imageMap.initMapper("ImageMap", &imageM, true);
				texturesInit = true;
			}
			std::cout << "Filepath is: " << resourcefilepath << std::endl;
			printf_s("Checking if file has already been loaded\n");
			if (imageMap.getElement(FileName))
				isLoaded = true;
			else
				isLoaded = false;

			// if file has not been loaded, load it
			if (!isLoaded)
			{
				image = IMG_Load((resourcefilepath).c_str());
				// FIX THIS
				//ImageResource *img = new ImageResource(image);
				if (!image)
					printf("IMG_Load: %s\n", IMG_GetError());


				// TODO: KEKSI MITEN IMAGET MAPPIIN LAITAN
				loadedResource = new ImageResource(image);
				imageMap.addElement(FileName, resourcefilepath, loadedResource);

				return (T*)loadedResource;
				SDL_FreeSurface(image);

			}
			// if file has already been loaded, skip loading
			else if (isLoaded)
			{
				T * img = (T*)imageMap.getElement(FileName);
				printf_s("File %s already loaded\n", FileName.c_str());
				printf_s("Increasing reference count for file: %s\n\n", FileName.c_str());
				img->incReferences();
				
				return img;
			}
		}

		// Init MODEL manager and map, load file to map
		else if (typeid(T).hash_code() == typeid(Object3D).hash_code())
		{
			if (!modelInit)
			{
				modelM.initResourceManager("ModelDataBase");
				modelMap.initMapper("ModelMap", &modelM, true);
				modelInit = true;
			}
			printf_s("Checking if file has already been loaded\n");
			if (modelMap.getElement(FileName))
				isLoaded = true;
			else
				isLoaded = false;

			// If file had not been loaded, load it
			if (!isLoaded)
			{
				obj = new Object3D;
				model = obj->loadModel(resourcefilepath);

				loadedResource = new Object3D(*model);
				modelMap.addElement(FileName, resourcefilepath, loadedResource);
				
				return (T*)loadedResource;
			}
			// If file has already been loaded, skip loading
			else if (isLoaded)
			{
				T * model = (T*)modelMap.getElement(FileName);
				printf_s("File %s already loaded\n", FileName.c_str());
				printf_s("Increasing reference count for file: %s\n\n", FileName.c_str());
				model->incReferences();
				
				return model;
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
			std::cout << "Filepath is: " << resourcefilepath << std::endl;
			printf_s("Checking if file has already been loaded\n");
			if (audioMap.getElement(FileName))
				isLoaded = true;
			else
				isLoaded = false;

			// if file has not been loaded, load it
			if (!isLoaded)
			{
				sound = Mix_LoadWAV((resourcefilepath).c_str());
				if (!sound)
					printf_s("Mix_LoadWAV: %s\n", Mix_GetError);

				loadedResource = new Audio(sound);
				audioMap.addElement(FileName, resourcefilepath, loadedResource);
				
				return (T*)loadedResource;
				Mix_FreeChunk(sound);
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
		else if (typeid(T).hash_code() == typeid(std::string).hash_code())
		{
			if (!txtInit)
			{
				txtM.initResourceManager("TextDataBase");
				txtMap.initMapper("TextMap", &txtM, true);
				txtInit = true;
			}
			std::cout << "Filepath is: " << resourcefilepath << std::endl;
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

				return (T*)loadedResource;
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

	ResourceManager<ResourceBase>imageM;
	ResourceMap<ResourceBase>imageMap;

	Object3D *obj;
	std::vector<Mesh> *model;	// for all model files
	ResourceManager<ResourceBase>modelM;
	ResourceMap<ResourceBase>modelMap;

	Mix_Chunk *sound = NULL;		// for all audio files
	ResourceManager<ResourceBase>audioM;
	ResourceMap<ResourceBase>audioMap;

	SDL_RWops *txt = NULL;		// for shaders/text files
	std::string txtcontent;
	ResourceManager<ResourceBase>txtM;
	ResourceMap<ResourceBase>txtMap;

	bool texturesInit = false;
	bool modelInit = false;
	bool audioInit = false;
	bool txtInit = false;

	int fileSize = 0;

};

#endif