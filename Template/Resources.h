#ifndef Resources_H
#define Resources_H

#include "ResourceBase.h"
#include "Core.h"
#include "Texture.h"
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
		if (typeid(T).hash_code() == typeid(Texture).hash_code())
		{
			if (!texturesInit)
			{
				textureM.initResourceManager("TextureDataBase");
				textureMap.initMapper("TextureMap", &textureM, true);
				texturesInit = true;
			}
			// check if file has already been loaded
			if (textureMap.getElement(FileName))
				isLoaded = true;
			else if (!textureMap.getElement(FileName))
				isLoaded = false;

			// if file has not been loaded, load it
			if (!isLoaded)
			{
				image = IMG_Load((resourcefilepath).c_str());

				if (!image)
					printf("IMG_Load: %s\n", IMG_GetError());

				loadedResource = new Texture(resourcefilepath, image);

				textureMap.addElement(FileName, resourcefilepath, loadedResource);
			}
			// if file has already been loaded, skip loading
			else if (isLoaded)
			{
				T * tex = (T*)textureMap.getElement(FileName);
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

			if (audioMap.getElement(FileName))
				isLoaded = true;
			else if (!audioMap.getElement(FileName))
				isLoaded = false;

			// if file has not been loaded, load it
			if (!isLoaded)
			{
				sound = Mix_LoadMUS((resourcefilepath).c_str());
				if (!sound)
					printf_s("Mix_LoadMus: %s\n", Mix_GetError);

				loadedResource = new Audio(resourcefilepath, sound);

				audioMap.addElement(FileName, resourcefilepath, loadedResource);
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

			if (txtMap.getElement(FileName))
				isLoaded = true;
			else if (!txtMap.getElement(FileName))
				isLoaded = false;

			// if file has not been loaded, load it
			if (!isLoaded)
			{
				SDL_RWops *txt = SDL_RWFromFile(resourcefilepath.c_str(), "r");
				if (txt == NULL) {
					fprintf(stderr, "Couldn't open %s\n", FileName.c_str());
				}


			/*	std::ifstream txtFile(resourcefilepath.c_str(), std::ios::binary | std::ios::ate);
				std::ifstream::pos_type fileSize = txtFile.tellg();
				txtFile.seekg(0, std::ios::beg);

				std::vector<char> bytes(fileSize);
				txtFile.read(&bytes[0], fileSize);

				std::string string(&bytes[0], fileSize);
				std::cout << "" << string << std::endl;*/

				loadedResource = new Text(resourcefilepath, txt);


				txtMap.addElement(FileName, resourcefilepath, loadedResource);
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

		//// Shader
		//else if (typeid(T).hash_code() == typeid(std::string).hash_code())
		//	loadedResource = txt.Load(ShaderString.assign((std::istreambuf_iterator< char >(resourcefilepath).c_str()), std::istreambuf_iterator<char>());
		//


		//return (T*)loadedResource;

		// find "." in string
		/*std::string extension = "";
		size_t pos = resourcefilepath.find_last_of(".");*/

		//// check if position is valid
		//if (pos != std::string::npos)
		//	extension = resourcefilepath.substr(pos + 1);
		//
		////compare to IMAGE extensions
		//if (extension == "png" | extension == "jpeg" | extension == "webp")
		//	loadImage(resourcefilepath);

		//compare to AUDIO extensions
		//else if (extension == "wav" | extension == "mp3" | extension == "flac" | extension == "ogg")
		//	loadSound(resourcefilepath);

		////compare to SHADER extensions
		//else if (extension == "glfs" | extension == "glvs")
		//	loadShader(resourcefilepath);
		//
		////compare to FONT extensions
		//else if (extension == "ttf")
		//	loadFont(resourcefilepath);
		//
		////compare to AUDIO extensions
		//else if (extension == "glfs" | extension == "glvs")
		//	loadShader(resourcefilepath);
		//
		////compare to 3D MODEL extensions
		//else if (extension == "obj" | extension == "blend" | extension == "dae" 
		//	| extension == "xml" | extension == "3ds" | extension == "ase" 
		//	| extension == "smd" | extension == "vta" | extension == "x" 
		//	| extension == "dxf")
		//	load3DModel(resourcefilepath);

		//else
		//	printf_s("Could not determine file extension\n");
	}
	// esim sprite luokkaan SDL_Surface*Sprite::Load(filepath)
	//Texture* loadImage(const std::string &resourcefilepath)
	//{
	//	image = IMG_Load((resourcefilepath).c_str());
	//	
	//	if (!image)
	//	{
	//		printf_s("IMG_Load: %s\n", IMG_GetError());
	//		//handle error
	//	}
	//	else
	//		printf_s("Image file %s loaded succesfully!\n", resourcefilepath.c_str());

	//	texture = new Texture(image);

	//	return texture;
	//}

	//Audio loadSound(const std::string &resourcefilepath)
	//{
	//	// WAV-filuja ei voi ladata Mix_LoadMUS:n avulla, tarvitsee Mix_LoadWAV koska syyt
	//	// ehkä mixerin vaihto openAL ????
	//			
	//	sound = Mix_LoadMUS((resourcefilepath).c_str());
	//	
	//	if (!sound)
	//	{
	//		printf("Mix_LoadMUS: %s\n", Mix_GetError());
	//	}
	//	else
	//		printf_s("Audio file %s loaded succesfully!\n", resourcefilepath.c_str());
	//	audio = new Audio(sound);

	//	return *audio;
	//}

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

	ResourceManager<ResourceBase>textureM;
	ResourceMap<ResourceBase>textureMap;

	Mix_Music *sound = NULL;		// for all audio files
	ResourceManager<ResourceBase>audioM;
	ResourceMap<ResourceBase>audioMap;

	SDL_RWops *txt = NULL;		// for shaders/text files
	ResourceManager<ResourceBase>txtM;
	ResourceMap<ResourceBase>txtMap;


	/*ResourceManager<Audio> audioM;
	ResourceMap<Audio>audioMap;*/
	bool texturesInit = false;
	bool audioInit = false;
	bool txtInit = false;

	std::string FileName;


};

#endif