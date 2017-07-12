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

#include <SDL2pp/EventHandler.hh>

using namespace std;

namespace SDL2pp {

void EventHandler::OnKeyDown(SDL_KeyboardEvent) { }

void EventHandler::OnKeyUp(SDL_KeyboardEvent) { }

void EventHandler::OnMouseMotion(SDL_MouseMotionEvent) { }

void EventHandler::OnMouseButtonDown(SDL_MouseButtonEvent) { }

void EventHandler::OnMouseButtonUp(SDL_MouseButtonEvent) { }

void EventHandler::OnMouseWheel(SDL_MouseWheelEvent) { }

void EventHandler::OnUnkownEvent(SDL_Event) { }

bool EventHandler::PollOneEvent() {
	// Static to prevent re-instantiation for every call
	// the actual value shouldn't matter
	static SDL_Event event;
	return PollOneEvent(event);
}

bool EventHandler::PollOneEvent(SDL_Event& event) {
	if (!SDL_PollEvent(&event)) {
		return false;
	}
	
	if (SDL_KEYDOWN == event.type) { OnKeyDown(event.key); }
	else if (SDL_KEYUP == event.type) { OnKeyUp(event.key); }
	else if (SDL_MOUSEMOTION == event.type) { OnMouseMotion(event.motion); }
	else if (SDL_MOUSEBUTTONDOWN == event.type) { OnMouseButtonUp(event.button); }
	else if (SDL_MOUSEBUTTONUP == event.type) { OnMouseButtonUp(event.button); }
	else if (SDL_MOUSEWHEEL == event.type) { OnMouseWheel(event.wheel); }
	else { OnUnkownEvent(event); }
	
	return true;
}

vector<SDL_Event> EventHandler::PollAllEvents() {
	vector<SDL_Event> events;
	
	SDL_Event event;
	while (PollOneEvent(event)) {
		events.push_back(event);
	}
	
	return events;
}

}
