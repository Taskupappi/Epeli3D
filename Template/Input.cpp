#include "Input.h"
using namespace core;

Input::Input() :_exit(false)
{

}

Input::~Input()
{}

bool Input::pollInputs()
{
	bool processedInputs = false;
	SDL_Event ev;
	SDL_PollEvent(&ev);
	//Gets all input events
	while (SDL_PollEvent(&ev))
	{
		if (!processedInputs)
		{
			//Clears previous keys
			//_pressedKeys.clear();
			//_releasedKeys.clear();
			processedInputs = true;
		}
		switch (ev.type)
		{
		case SDL_QUIT: //Window closing
			_exit = true;
			break;
		case SDL_KEYDOWN:
			SDL_Log("Key Down %i", ev.key.keysym.scancode);
			//SDL_Log("%s", message.c_str());
			//_pressedKeys.push_back(ev.key.keysym.sym);
			break;
		case SDL_KEYUP:
			SDL_Log("Key Up %i", ev.key.keysym.scancode);
			//_pressedKeys.push_back(ev.key.keysym.sym);
			break;
		default:
			break;
		}
	}
	return processedInputs;
}
bool Input::isKeyPressed(SDL_Keycode key)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_GetScancodeFromKey(key)]) 
	{
		return true;
	}
	//if(findKey(_pressedKeys,key))
	//	return true;
	return false;
}
bool Input::iskeyReleased(SDL_Keycode key)
{
	//if (SDL_GetKeyState());
	if (findKey(_releasedKeys, key))
		return true;
	return false;
}
bool Input::findKey(std::vector<SDL_Keycode> v, SDL_Keycode key)
{
	for (const SDL_Keycode &k : v)
	{
		if (k == key)
			return true;
	}
	return false;
}

void Input::addPressedKey(SDL_Keycode key)
{
	_pressedKeys.push_back(key);
}
void Input::addReleasedKey(SDL_Keycode key)
{
	_releasedKeys.push_back(key);
}
