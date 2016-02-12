#ifndef TESTIFOO_H
#define TESTIFOO_H

#include "ResourceBase.h"
#include "Core.h"

class TestiFoo :
	public ResourceBase
{
public:
	// this constructor must be present
	TestiFoo(const std::string &resourcefilename, void *args) : ResourceBase(resourcefilename, args){}

	// regular base constructor and destructor
	//TestiFoo(){}
	~TestiFoo(){}

	void loadFile(const std::string &resourcefilepath)
	{
		// find "." in string
		std::string extension = "";
		size_t pos = resourcefilepath.find_last_of(".");
		
		// check if position is valid
		if (pos != std::string::npos)
			extension = resourcefilepath.substr(pos + 1);
		
		//compare to IMAGE extensions
		if (extension == "png" | extension == "jpeg" | extension == "webp")
			loadImage(resourcefilepath);
		
		//compare to AUDIO extensions
		else if (extension == "wav" | extension == "mp3" | extension == "flac" | extension == "ogg")
			loadSound(resourcefilepath);
		
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
		
		else
			printf_s("Could not determine file extension\n");
	}
	// esim sprite luokkaan SDL_Surface*Sprite::Load(filepath)
	void loadImage(const std::string &resourcefilepath)
	{
		image = IMG_Load((resourcefilepath).c_str());
		
		if (!image)
		{
			printf_s("IMG_Load: %s\n", IMG_GetError());
			//handle error
		}
		else
			printf_s("Image file %s loaded succesfully!\n", resourcefilepath.c_str());
	}

	void loadSound(const std::string &resourcefilepath)
	{
		// ehk‰ mixerin vaihto openAL ????
				
		// antaa erroria, yritt‰‰ ehk‰ v‰kisell‰ toistaa?
		//audio = Mix_LoadMUS(resourcefilepath.c_str());
		
		if (!audio)
		{
			printf("Mix_LoadMUS: %s\n", Mix_GetError());
		}
		else
			printf_s("Audio file %s loaded succesfully!\n", resourcefilepath.c_str());
	}

private:
	////////////////////////////////////
	// copy constructor and overload operator are private
	// no copies allowed since classes are referenced

	TestiFoo(const TestiFoo &foo) : ResourceBase(foo){}

	TestiFoo &operator =(TestiFoo &foo)
	{
		if (this == &foo)
			return *this;
		return *this;
	}

	SDL_Surface *image = 0;
	Mix_Music *audio = 0;
};

#endif