#include <SDL_main.h>

#include <SDL2pp/EventHandler.hh>

#include "testing.h"

#include <cstdlib>
#include <ctime>

using namespace SDL2pp;

class TestEventHandler : public EventHandler {
	int unkownEvent_ = 0;
	
	void OnUnkownEvent(SDL_Event) override {
		unkownEvent_++;
	}
	
public:
	int GetUnkownEvent() const { return unkownEvent_; }
};

// For the event types event type
constexpr Uint32 UNKOWN_EVENT = SDL_LASTEVENT - 1;

BEGIN_TEST(int, char*[])
	// Test no event captured
	{
		TestEventHandler eventHandler;
		
		EXPECT_EQUAL((bool)eventHandler.PollOneEvent(), false);
		EXPECT_EQUAL(eventHandler.PollAllEvents().empty(), true);
	}

	// Test polling a single event and retrieving a single one
	{
		SDL_Event event;
		event.type = UNKOWN_EVENT;
		event.common.timestamp = static_cast<int>((intptr_t)&event); // Random value
		SDL_PushEvent(&event);
		
		TestEventHandler eventHandler;
		auto polledEvent = eventHandler.PollOneEvent();
		EXPECT_EQUAL((bool)polledEvent, true);
		EXPECT_EQUAL(eventHandler.GetUnkownEvent(), 1);
		
		EXPECT_EQUAL(polledEvent->type, event.type);
		EXPECT_EQUAL(polledEvent->common.timestamp, event.common.timestamp);
		
		EXPECT_EQUAL((bool)eventHandler.PollOneEvent(), false);
		EXPECT_EQUAL(eventHandler.PollAllEvents().empty(), true);
	}

	// Test polling a single event and retrieving all events
	{
		SDL_Event event;
		event.type = UNKOWN_EVENT;
		event.common.timestamp = static_cast<int>((intptr_t)&event); // Random value
		SDL_PushEvent(&event);
		
		TestEventHandler eventHandler;
		auto polledEvents = eventHandler.PollAllEvents();
		EXPECT_EQUAL(polledEvents.size(), static_cast<size_t>(1));
		EXPECT_EQUAL(eventHandler.GetUnkownEvent(), 1);
		
		EXPECT_EQUAL(polledEvents[0].type, event.type);
		EXPECT_EQUAL(polledEvents[0].common.timestamp, event.common.timestamp);
		
		EXPECT_EQUAL((bool)eventHandler.PollOneEvent(), false);
		EXPECT_EQUAL(eventHandler.PollAllEvents().empty(), true);
	}

	// Test polling several events and retrieving one by one
	{
		constexpr int eventCount = 5;
		SDL_Event events[eventCount];
		for (auto& event : events) {
			event.type = UNKOWN_EVENT;
			event.user.code = static_cast<int>((intptr_t)&event); // Random value
			SDL_PushEvent(&event);
		}
		
		TestEventHandler eventHandler;
		for (auto event : events) {
			auto polledEvent = eventHandler.PollOneEvent();
			EXPECT_EQUAL((bool)polledEvent, true);
			EXPECT_EQUAL(polledEvent->type, event.type);
			EXPECT_EQUAL(polledEvent->user.code, event.user.code);
		}
		EXPECT_EQUAL(eventHandler.GetUnkownEvent(), eventCount);
		
		EXPECT_EQUAL((bool)eventHandler.PollOneEvent(), false);
		EXPECT_EQUAL(eventHandler.PollAllEvents().empty(), true);
	}

	// Test polling several events and retrieving all events
	{
		constexpr int eventCount = 5;
		SDL_Event events[eventCount];
		for (auto& event : events) {
			event.type = UNKOWN_EVENT; // Use a random event type
			event.user.code = static_cast<int>((intptr_t)&event); // Random value
			SDL_PushEvent(&event);
		}
		
		TestEventHandler eventHandler;
		auto polledEvents = eventHandler.PollAllEvents();
		EXPECT_EQUAL(polledEvents.size(), static_cast<size_t>(eventCount));
		for (int n = 0; n < eventCount; ++n) {
			EXPECT_EQUAL(polledEvents[n].type, events[n].type);
			EXPECT_EQUAL(polledEvents[n].user.code, events[n].user.code);
		}
		
		EXPECT_EQUAL((bool)eventHandler.PollOneEvent(), false);
		EXPECT_EQUAL(eventHandler.PollAllEvents().empty(), true);
	}
END_TEST()
