#include <SDL_main.h>

#include <SDL2pp/KeyboardEvents.hh>

#include "testing.h"

using namespace SDL2pp;

SDL_Event CreateKeyboardEvent(bool keydown, bool repeat, WindowIdForEvent windowID, SDL_Keycode keycode, SDL_Keymod mod);

BEGIN_TEST(int, char*[])
	// Test empty keyboard state
	{
		KeyboardEvents keyboardEvents;
		EXPECT_TRUE(!keyboardEvents.GetKeyState(SDLK_0));
		EXPECT_TRUE(!keyboardEvents.GetKeyState(SDLK_ESCAPE));
		EXPECT_TRUE(keyboardEvents.GetEventList().empty());
		EXPECT_TRUE(!keyboardEvents.GetWindowId());
	}

	// Test keyboard state for all windows with empty event list
	{
		EventList events = EventList();
		KeyboardEvents keyboardEvents(events);
		EXPECT_TRUE(!keyboardEvents.GetKeyState(SDLK_0));
		EXPECT_TRUE(!keyboardEvents.GetKeyState(SDLK_ESCAPE));
		EXPECT_TRUE(keyboardEvents.GetEventList().empty());
		EXPECT_TRUE(!keyboardEvents.GetWindowId());
	}

	// Test keyboard state for all windows with different type of events
	{
		EventList events;
		// Add non-keyboard events
		for (auto type : { SDL_QUIT, SDL_MOUSEMOTION, SDL_WINDOWEVENT }) {
			SDL_Event event;
			event.type = type;
			events.push_back(event);
		}
		
		// Add a couple of keyboard related events, have it separate for quick assert
		EventList keyboardSpecificEvents = {
			CreateKeyboardEvent(true, false, 1, SDLK_x, KMOD_NONE),
			CreateKeyboardEvent(false, true, 2, SDLK_v, KMOD_RCTRL)
		};
		
		// Merge the events list
		events.insert(events.end(), keyboardSpecificEvents.begin(), keyboardSpecificEvents.end());
		
		KeyboardEvents keyboardEvents(events);
		EXPECT_EQUAL(*keyboardEvents.GetKeyState(SDLK_x), KeyState(true, false, KMOD_NONE));
		EXPECT_EQUAL(*keyboardEvents.GetKeyState(SDLK_v), KeyState(false, true, KMOD_RCTRL));
		EXPECT_EQUAL(keyboardEvents.GetEventList().size(), keyboardSpecificEvents.size());
		EXPECT_TRUE(!keyboardEvents.GetWindowId());
	}

	// Test keyboard state for all windows with keyboard events for any window
	{
		EventList events = {
			CreateKeyboardEvent(true, false, 1, SDLK_a, KMOD_NONE),
			CreateKeyboardEvent(false, true, 3, SDLK_ESCAPE, KMOD_NONE),
			CreateKeyboardEvent(true, false, 2, SDLK_x, KMOD_LALT)
		};
		KeyboardEvents keyboardEvents(events);
		EXPECT_EQUAL(*keyboardEvents.GetKeyState(SDLK_a), KeyState(true, false, KMOD_NONE));
		EXPECT_EQUAL(*keyboardEvents.GetKeyState(SDLK_ESCAPE), KeyState(false, true, KMOD_NONE));
		EXPECT_EQUAL(*keyboardEvents.GetKeyState(SDLK_x), KeyState(true, false, KMOD_LALT));
		EXPECT_TRUE(!keyboardEvents.GetKeyState(SDLK_q));
		EXPECT_EQUAL(keyboardEvents.GetEventList().size(), events.size());
		EXPECT_TRUE(!keyboardEvents.GetWindowId());
	}

	// Test keyboard state for specific window
	{
		EventList eventsForWindow1 = {
			CreateKeyboardEvent(true, false, 1, SDLK_x, KMOD_NONE),
			CreateKeyboardEvent(true, false, 1, SDLK_y, KMOD_RCTRL)
		};
		EventList eventsForWindow2 =  {
			CreateKeyboardEvent(false, false, 2, SDLK_x, KMOD_NONE),
			CreateKeyboardEvent(true, false, 2, SDLK_y, KMOD_LGUI),
			CreateKeyboardEvent(true, false, 2, SDLK_z, KMOD_NONE)
		};
		
		// Merge the events list
		EventList events;
		events.insert(events.end(), eventsForWindow1.begin(), eventsForWindow1.end());
		events.insert(events.end(), eventsForWindow2.begin(), eventsForWindow2.end());
		
		KeyboardEvents keyboardEvents(1, events);
		EXPECT_EQUAL(*keyboardEvents.GetKeyState(SDLK_x), KeyState(true, false, KMOD_NONE));
		EXPECT_EQUAL(*keyboardEvents.GetKeyState(SDLK_y), KeyState(true, false, KMOD_RCTRL));
		EXPECT_TRUE(!keyboardEvents.GetKeyState(SDLK_z));
		EXPECT_EQUAL(keyboardEvents.GetEventList().size(), eventsForWindow1.size());
		EXPECT_EQUAL(*keyboardEvents.GetWindowId(), WindowIdForEvent{1});
	}
END_TEST()

SDL_Event CreateKeyboardEvent(bool keydown, bool repeat, WindowIdForEvent windowID, SDL_Keycode keycode, SDL_Keymod mod) {
	SDL_Event result;
	result.key.type = keydown ? SDL_KEYDOWN : SDL_KEYUP;
	result.key.windowID = windowID;
	result.key.state = keydown ? SDL_PRESSED : SDL_RELEASED;
	result.key.repeat = repeat;
	result.key.keysym.sym = keycode;
	result.key.keysym.mod = mod;
	return result;
}
