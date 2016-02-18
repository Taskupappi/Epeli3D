#ifndef INPUT_H
#define INPUT_H
#include <vector>
//SDL
#include <SDL/SDL.h>
#include <glm/vec2.hpp>
#include "Mouse.h"

namespace core
{
	class Engine;

	class Input
	{
		
		friend class core::Engine;
		friend class Mouse;
	public:

		bool isMousePressed(Mouse::mButton b);
		bool isMouseReleased(Mouse::mButton b);
		const glm::vec2 getMousePosition(){ return _mouse._position; }
		const glm::vec2 getMouseMovement(){ return _mouse._movement; }

		void addPressedKey(SDL_Keycode key);
		void addReleasedKey(SDL_Keycode key);
		void clearKeys()
		{_pressedKeys.clear();_releasedKeys.clear();}
		bool isKeyPressed(SDL_Keycode key);
		bool iskeyReleased(SDL_Keycode key);
		const bool isClosing(void){ return _exit; }
		std::vector<SDL_Keycode> _pressedKeys;
		std::vector<SDL_Keycode> _releasedKeys;
		//Returns true if any key is pressed
		bool isKeyPressed(){ return !_pressedKeys.empty(); }
	protected:
		Input();
		~Input();
		Mouse _mouse;
	private:
		bool _exit;
		//Not used
		bool pollInputs();
		bool findKey(std::vector<SDL_Keycode>, SDL_Keycode key);
		
	};
}
#endif
