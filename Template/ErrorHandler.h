#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
//win include
#include <iostream>
#include <string>
//SDL include
#include <SDL_assert.h>
#include <SDL.h>

namespace core
{
	class ErrorHandler : public std::exception
	{
	public:
		ErrorHandler(){};
		~ErrorHandler(){};
		void writeLog(std::string message);
		void readAssert();
	private:

	};
}
#endif ErrorHandler