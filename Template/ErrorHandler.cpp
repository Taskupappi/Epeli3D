#include "ErrorHandler.h"

using namespace core;

void ErrorHandler::writeLog(std::string message)
{
	SDL_Log("%s", message.c_str());
}

void ErrorHandler::readAssert()
{
	const SDL_assert_data *item = SDL_GetAssertionReport();
	while (item)
	{
		printf("'%s', %s (%s:%d), triggered %u times, always ignore: %s.\n",
			item->condition, item->function, item->filename,
			item->linenum, item->trigger_count,
			item->always_ignore ? "yes" : "no");
		item = item->next;
	}
	SDL_ResetAssertionReport();
}