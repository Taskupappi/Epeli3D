#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H

#include "Component.h"
#include <string>
#include <vector>
#include "Object3D.h"

//class Object3D;
class Mesh;

class ModelComponent : public Component
{
public:
	ModelComponent();
	~ModelComponent();
	std::vector<Mesh>* loadModel(std::string filepath);
	void update(float deltaTime);
	Object3D* getModelData();
	std::vector<Mesh>* getModelMesh(){ return model->getMeshVecPtr(); }
	
private:
	Object3D* model;
	std::vector<Mesh>* modelMesh;
};
#endif