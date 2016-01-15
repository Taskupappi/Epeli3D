#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void loadImage();
	void load3DModel();
	void loadShader();
	void loadFont();
	void loadSound();

};

#endif