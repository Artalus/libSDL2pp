#include <SDL_main.h>

#include <SDL2pp/EventUtils.hh>

#include "testing.h"

using namespace SDL2pp;
using namespace std;

BEGIN_TEST(int, char*[])
	{
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		
		EXPECT_TRUE(EventIs(event, SDL_KEYDOWN));
		EXPECT_TRUE(EventIs(event, SDL_KEYDOWN, SDL_QUIT));
		
		EXPECT_TRUE(!EventIs(event, SDL_QUIT));
		EXPECT_TRUE(!EventIs(event, SDL_KEYUP, SDL_QUIT));
	}

	{
		SDL_Event event;
		
		event.type = SDL_USEREVENT;
		EXPECT_EQUAL("USEREVENT", GetEventName(event));
		
		event.type = SDL_LASTEVENT - 1;
		EXPECT_EQUAL("", GetEventName(event));
	}
END_TEST()
