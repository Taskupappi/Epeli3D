#ifndef _3DOBJECTMANAGER_H
#define _3DOBJECTMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Object3D.h"

class ObjectManager
{
public:
	


private:
	std::vector<Object3D> ObjectDatas; //pit‰‰ olla luultavasti map
	std::string directory;

};






#endif