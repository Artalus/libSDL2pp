#include <SDL_main.h>

#include <SDL2pp/EventManager.hh>
#include <SDL2pp/Exception.hh>

#include "testing.h"

using namespace SDL2pp;

void RegisterEvent(SDL_Event event);

BEGIN_TEST(int, char*[])
	// Test empty event manager
	{
		EventManager eventManager;
		KeyboardEvents keyboardEvents = eventManager.GetKeyboardEvents();
		KeyboardEvents keyboardEventsWindow1 = eventManager.GetKeyboardEvents(1);
		KeyboardEvents keyboardEventsWindow2 = eventManager.GetKeyboardEvents(100);
		
		EXPECT_TRUE(eventManager.GetCapturedEvents().empty());
		EXPECT_TRUE(keyboardEvents.GetEventList().empty());
		EXPECT_TRUE(keyboardEventsWindow1.GetEventList().empty());
		EXPECT_TRUE(keyboardEventsWindow2.GetEventList().empty());
		EXPECT_TRUE(!eventManager.QuitEventCaptured());
	}

	// Test capturing a quit event
	{
		SDL_Event quitEvent;
		quitEvent.type = SDL_QUIT;
		RegisterEvent(quitEvent);
	
		EventManager eventManager;
		eventManager.CaptureEvents();
		
		KeyboardEvents keyboardEvents = eventManager.GetKeyboardEvents();
		KeyboardEvents keyboardEventsWindow1 = eventManager.GetKeyboardEvents(1);
		KeyboardEvents keyboardEventsWindow2 = eventManager.GetKeyboardEvents(100);
		
		EXPECT_EQUAL(eventManager.GetCapturedEvents().size(), 1);
		EXPECT_TRUE(keyboardEvents.GetEventList().empty());
		EXPECT_TRUE(keyboardEventsWindow1.GetEventList().empty());
		EXPECT_TRUE(keyboardEventsWindow2.GetEventList().empty());
		EXPECT_TRUE(eventManager.QuitEventCaptured());
		EXPECT_EQUAL(eventManager.GetCapturedEvents().size(), 1);
	}

	// Test capturing a keyboard event
	{
		SDL_Event keyboardEvent;
		keyboardEvent.type = SDL_KEYDOWN;
		keyboardEvent.key.windowID = 1;
		RegisterEvent(keyboardEvent);
		keyboardEvent.key.windowID = 2;
		RegisterEvent(keyboardEvent);
		RegisterEvent(keyboardEvent);
		
		EventManager eventManager;
		eventManager.CaptureEvents();
		
		KeyboardEvents keyboardEvents = eventManager.GetKeyboardEvents();
		KeyboardEvents keyboardEventsWindow1 = eventManager.GetKeyboardEvents(1);
		KeyboardEvents keyboardEventsWindow2 = eventManager.GetKeyboardEvents(2);
		KeyboardEvents keyboardEventsWindow3 = eventManager.GetKeyboardEvents(100);
		
		EXPECT_EQUAL(keyboardEvents.GetEventList().size(), 3);
		EXPECT_TRUE(keyboardEventsWindow1.GetEventList().size(), 1);
		EXPECT_TRUE(keyboardEventsWindow2.GetEventList().size(), 2);
		EXPECT_TRUE(keyboardEventsWindow3.GetEventList().empty());
		EXPECT_TRUE(!eventManager.QuitEventCaptured());
		EXPECT_EQUAL(eventManager.GetCapturedEvents().size(), 3);
	}
END_TEST()

void RegisterEvent(SDL_Event event) {
	if (SDL_PushEvent(&event) < 0) {
		throw Exception("SDL_PushEvent");
	}
}
