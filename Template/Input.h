#ifndef INPUT_H
#define INPUT_H
#include <vector>
//SDL
#include <SDL/SDL.h>

namespace core
{
	class Engine;
	class Input
	{
		friend class core::Engine;

	public:

		void addPressedKey(SDL_Keycode key);
		void addReleasedKey(SDL_Keycode key);
		void clearKeys()
		{_pressedKeys.clear();_releasedKeys.clear();}
		bool isKeyPressed(SDL_Keycode key);
		bool iskeyReleased(SDL_Keycode key);
		const bool isClosing(void){ return _exit; }
		std::vector<SDL_Keycode> _pressedKeys;
		std::vector<SDL_Keycode> _releasedKeys;
	protected:
		Input();
		~Input();
	private:
		bool _exit;
		bool pollInputs();
		bool findKey(std::vector<SDL_Keycode>, SDL_Keycode key);
	};

	
}
#endif
