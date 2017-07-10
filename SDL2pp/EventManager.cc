/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2017 Vraiment <jemc44@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <SDL2pp/EventManager.hh>

#include <SDL2pp/Optional.hh>

#include <algorithm>

namespace SDL2pp {
	void EventManager::CaptureEvents() {
		EventList newEvents;
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			newEvents.push_back(event);
		}
		
		quitEventCache = NullOpt;
		keyboardEventsCache = NullOpt;
		keyboardEventsCacheByWindow.clear();
		events = newEvents;
	}
	
	KeyboardEvents EventManager::GetKeyboardEvents() const {
		if (!keyboardEventsCache) {
			keyboardEventsCache = KeyboardEvents(events);
		}
		
		return *keyboardEventsCache;
	}
	
	KeyboardEvents EventManager::GetKeyboardEvents(WindowIdForEvent windowId) const {
		auto keyboardState = keyboardEventsCacheByWindow.find(windowId);
		if (keyboardState == keyboardEventsCacheByWindow.end()) {
			return keyboardEventsCacheByWindow[windowId] = KeyboardEvents(windowId, events);
		}
		
		return keyboardState->second;
	}
	
	bool EventManager::QuitEventCaptured() const {
		if (!quitEventCache) {
			auto quitEvent = std::find_if(
				events.begin(),
				events.end(),
				[](SDL_Event event) { return SDL_QUIT == event.type; });
			
			quitEventCache = events.end() != quitEvent;
		}
		
		return *quitEventCache;
	}
	
	EventList EventManager::GetCapturedEvents() const {
		return events;
	}
}
