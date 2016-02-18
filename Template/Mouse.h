#ifndef MOUSE_H
#define MOUSE_H
#include <glm/vec2.hpp>
namespace core
{
	class Engine;
	class Mouse
	{
		friend class Input;
		friend class Engine;
	public:
		const glm::vec2 getPosition(){ return _position; }
		const glm::vec2 getMovement(){ return _movement; }
		enum mButton { left = 1, middle = 2, right = 3 };
		enum mBstate{ unknown = 0, pressed = 1, released = 2 };
		struct button
		{
			mButton b;
			mBstate bs;
		};

		const Mouse::button getButton(Mouse::mButton mB)
		{
			switch (mB)
			{
			case Mouse::right:
				return button3;
				break;
			case Mouse::middle:
				return button2;
				break;
			default:
				return button1;
				break;
			}
		}

	protected:
		void setMouseMovement(glm::vec2 position, glm::vec2  movement)
		{
			_position = position;
			_movement = movement;
		}
		void setMouseBState(mButton b, mBstate s)
		{
			if (b == Mouse::left)
				button1.bs = s;
			else if (b == Mouse::middle)
				button2.bs = s;
			else
				button3.bs = s;
		}

		Mouse()
		{
			button1.b = Mouse::left;
			button2.b = Mouse::middle;
			button3.b = Mouse::right;

			button1.bs = Mouse::unknown;
			button2.bs = Mouse::unknown;
			button3.bs = Mouse::unknown;
		};
		~Mouse(){};
	private:
		button button1;
		button button2;
		button button3;
		glm::vec2 _position;
		glm::vec2 _movement;
	};
}
#endif