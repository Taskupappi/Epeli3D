#include "ModelComponent.h"

ModelComponent::ModelComponent()
	:Component(COMPONENTID::MODEL)
{
	model = nullptr;
}

ModelComponent::~ModelComponent()
{
	delete model;
}

void ModelComponent::loadModel(const std::string filepath)
{
	model->loadModel(filepath);
}

void ModelComponent::update(float deltaTime)
{

}