#ifndef COMPONENT_H
#define COMPONENT_H

enum COMPONENTID
{
	MODEL = 1,
	SPRITE = 2,
	TRANSLATION = 3
};

class Component
{
public:
	Component(unsigned id){ this->id = id; };
	~Component(){};
	virtual void update(float deltaTime) = 0;

private:
	unsigned id;
};
#endif