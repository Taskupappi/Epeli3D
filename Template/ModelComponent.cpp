#include "ModelComponent.h"

//class engine;

ModelComponent::ModelComponent()
{
	model = nullptr;
}

ModelComponent::~ModelComponent()
{
	delete model;
}

std::vector<Mesh>* ModelComponent::loadModel(std::string filepath)
{
	model = new Object3D();
	return model->loadModel(filepath);
}

void ModelComponent::update(float deltaTime)
{

}

Object3D* ModelComponent::getModelData()
{
	return model;
}