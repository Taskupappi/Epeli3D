#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H

#include "Object3D.h"
#include "Component.h"

class ModelComponent : public Component
{
public:
	ModelComponent();
	~ModelComponent();
	void loadModel(const std::string filepath);
	void update(float deltaTime);
private:
	Object3D *model;
};
#endif