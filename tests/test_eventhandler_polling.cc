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

constexpr Uint32 UNKOWN_EVENT = SDL_LASTEVENT - 1;

BEGIN_TEST(int, char*[])
	// Test no event captured
	{
		TestEventHandler eventHandler;
		
		EXPECT_TRUE(!eventHandler.PollOneEvent());
		EXPECT_TRUE(eventHandler.PollAllEvents().empty());
	}

	// Test polling a single event with one event
	{
		SDL_Event event;
		event.type = UNKOWN_EVENT;
		event.common.timestamp = rand();
		SDL_PushEvent(&event);
		
		TestEventHandler eventHandler;
		auto polledEvent = eventHandler.PollOneEvent();
		EXPECT_EQUAL((bool)polledEvent, true);
		EXPECT_EQUAL(eventHandler.GetUnkownEvent(), 1);
		
		EXPECT_EQUAL(polledEvent->type, event.type);
		EXPECT_EQUAL(polledEvent->common.timestamp, event.common.timestamp);
		
		EXPECT_TRUE(!eventHandler.PollOneEvent());
		EXPECT_EQUAL(eventHandler.PollAllEvents().empty(), true);
	}

	// Test polling a single event with all events
	{
		SDL_Event event;
		event.type = UNKOWN_EVENT;
		event.common.timestamp = static_cast<int>((intptr_t)&event); // Random value
		SDL_PushEvent(&event);
		
		TestEventHandler eventHandler;
		auto polledEvents = eventHandler.PollAllEvents();
		EXPECT_EQUAL(polledEvents.size(), (unsigned)1);
		EXPECT_EQUAL(polledEvents[0].type, event.type);
		EXPECT_EQUAL(polledEvents[0].common.timestamp, event.common.timestamp);
		EXPECT_EQUAL(eventHandler.GetUnkownEvent(), 1);
		
		EXPECT_TRUE(!eventHandler.PollOneEvent());
		EXPECT_EQUAL(eventHandler.PollAllEvents().empty(), true);
	}

	// Test polling several events one by one
	{
		constexpr int eventCount = 5;
		SDL_Event events[eventCount];
		for (auto& event : events) {
			event.type = UNKOWN_EVENT; // Use a random event type
			event.user.code = static_cast<int>((intptr_t)&event); // Random value
			SDL_PushEvent(&event);
		}
		
		TestEventHandler eventHandler;
		for (auto event : events) {
			SDL_Event polledEvent;
			EXPECT_EQUAL(eventHandler.PollOneEvent(polledEvent), true);
			EXPECT_EQUAL(polledEvent.type, event.type);
			EXPECT_EQUAL(polledEvent.user.code, event.user.code);
		}
		EXPECT_EQUAL(eventHandler.GetUnkownEvent(), eventCount);
		
		EXPECT_TRUE(!eventHandler.PollOneEvent());
		EXPECT_EQUAL(eventHandler.PollAllEvents().empty(), true);
	}

	// Test polling several events all together
	{
		constexpr int eventCount = 5;
		SDL_Event events[eventCount];
		for (auto& event : events) {
			event.type = UNKOWN_EVENT; // Use a random event type
			event.user.code = static_cast<int>((intptr_t)&event); // Random value
			SDL_PushEvent(&event);
		}
		
		TestEventHandler eventHandler;
		for (auto event : events) {
			SDL_Event polledEvent;
			EXPECT_EQUAL(eventHandler.PollOneEvent(polledEvent), true);
			EXPECT_EQUAL(polledEvent.type, event.type);
			EXPECT_EQUAL(polledEvent.user.code, event.user.code);
		}
		EXPECT_EQUAL(eventHandler.GetUnkownEvent(), eventCount);
		
		EXPECT_TRUE(!eventHandler.PollOneEvent());
		EXPECT_EQUAL(eventHandler.PollAllEvents().empty(), true);
	}
END_TEST()
