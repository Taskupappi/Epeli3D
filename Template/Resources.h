#ifndef Resources_H
#define Resources_H

#include "ResourceBase.h"
#include "Core.h"
#include "Texture.h"
#include "Audio.h"
#include <unordered_map>


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
		//T * loadedResource = nullptr;
		ResourceBase * loadedResource = NULL;
		// Init TEXTURE manager and map, load file to map
		if (typeid(T).hash_code() == typeid(Texture).hash_code())
		{
			if (!texturesInit)
			{
				texM.initResourceManager("TextureDataBase");
				txtMap.initMapper("TextureMap", &texM, true);
				texturesInit = true;
			}
			image = IMG_Load((resourcefilepath).c_str());

			if (!image)
				printf_s("Texture ei toimi\n");

			loadedResource = new Texture(resourcefilepath, image);

			txtMap.addElement(loadedResource->getResourceFileName(), resourcefilepath, loadedResource);

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
			sound = Mix_LoadMUS((resourcefilepath).c_str());
			if (!sound)
				printf_s("Audio ei toimi\n");

			loadedResource = new Audio(resourcefilepath, sound);

			audioMap.addElement(loadedResource->getResourceFileName(), resourcefilepath, loadedResource);
		}

		// Init STRING manager and map, load file to map
		//else if (typeid(T).hash_code() == typeid(std::string).hash_code())
		//{
		//	if (!stringInit)
		//	{
		//		stringM.initResourceManager("StringDataBase");
		//		stringMap.initMapper("StringMap", &stringM, true);
		//		stringInit = true;
		//	}
		//	/*sound = Mix_LoadMUS((resourcefilepath).c_str());
		//	if (!sound)
		//		printf_s("Audio ei toimi\n");

		//	loadedResource = new Audio(resourcefilepath, sound);*/
		//}

		//// Shader
		//else if (typeid(T).hash_code() == typeid(std::string).hash_code())
		//	loadedResource = txt.Load(ShaderString.assign((std::istreambuf_iterator< char >(resourcefilepath).c_str()), std::istreambuf_iterator<char>());
		//


		return (T*)loadedResource;

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

	ResourceManager<ResourceBase>texM;
	ResourceMap<ResourceBase>txtMap;

	Mix_Music *sound = NULL;		// for all audio files
	ResourceManager<ResourceBase>audioM;
	ResourceMap<ResourceBase>audioMap;

	//	std::string string = NULL;		// for shaders
	//ResourceManager<std::string>stringM;
	//ResourceMap<std::string>stringMap;


	/*ResourceManager<Audio> audioM;
	ResourceMap<Audio>audioMap;*/
	bool texturesInit = false;
	bool audioInit = false;
	bool stringInit = false;

	ResourceManager<std::string> txt;
};

#endif