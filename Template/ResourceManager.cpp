#include "ResourceManager.h"


void ResourceManager::loadResource(const std::string fileName)
{
	// find "." in string
	std::string extension = "";
	size_t pos = fileName.find_last_of(".");

	// check if position is valid
	if (pos != std::string::npos)
		extension = fileName.substr(pos + 1);

	//compare to IMAGE extensions
	if (extension == "png" | extension == "jpeg" | extension == "webp")
		loadImage(fileName);

	//compare to AUDIO extensions
	else if (extension == "wav" | extension == "mp3" | extension == "flac" | extension == "ogg")
		loadSound(fileName);

	//compare to SHADER extensions
	else if (extension == "glfs" | extension == "glvs")
		loadShader(fileName);

	//compare to FONT extensions
	else if (extension == "ttf")
		loadFont(fileName);

	//compare to AUDIO extensions
	else if (extension == "glfs" | extension == "glvs")
		loadShader(fileName);

	//compare to 3D MODEL extensions
	else if (extension == "obj" | extension == "blend" | extension == "dae" 
		| extension == "xml" | extension == "3ds" | extension == "ase" 
		| extension == "smd" | extension == "vta" | extension == "x" 
		| extension == "dxf")
		load3DModel(fileName);

	else
		printf_s("Could not determine file extension\n");
	/////////////////////////
}
void ResourceManager::loadImage(const std::string fileName)
{


	image = IMG_Load((imageFilePath + fileName).c_str());

	if (!image)
	{
		printf_s("IMG_Load: %s\n", IMG_GetError());
		//handle error
	}
}

void ResourceManager::load3DModel(const std::string fileName)
{
	//Jussi jatkaa tätä
}

void ResourceManager::loadShader(const std::string fileName)
{
	GLuint ShaderID = NULL;
	std::string ShaderString;
	std::ifstream SourceFile((shaderFilePath + fileName).c_str());

	if (SourceFile)
	{
		ShaderString.assign((std::istreambuf_iterator< char >(SourceFile)), std::istreambuf_iterator<char>());
	}
	else
	{
		std::cout << "unable to open source file" << std::endl;
	}
}

void ResourceManager::loadFont(const std::string fileName)
{
	//Samuli jatkaa tätä?
}

void ResourceManager::loadSound(const std::string fileName)
{
	// ehkä mixerin vaihto openAL ????


	// antaa erroria, yrittää ehkä väkisellä toistaa?
	audio = Mix_LoadMUS((audioFilePath + fileName).c_str());

	if (!audio)
	{
		printf("Mix_LoadMUS: %s\n", Mix_GetError());
	}
}