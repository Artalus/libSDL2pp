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

#include <SDL2pp/KeyboardEvents.hh>

#include <SDL2pp/KeyState.hh>

namespace SDL2pp {

KeyboardEvents::KeyboardEvents() {
}

KeyboardEvents::KeyboardEvents(const EventList events) : windowID_(), events_() {
	processEvents(events);
}

KeyboardEvents::KeyboardEvents(WindowIdForEvent windowID, const EventList events) : windowID_(windowID), events_() {
	processEvents(events);
}

void KeyboardEvents::processEvents(const EventList events) {
	for (auto event : events) {
		// Process and store the event only if is a key up/down event
		// and if we are asking for the same window id (empty window id means all events)
		if (EventIs(event, SDL_KEYDOWN, SDL_KEYUP) &&
			(!windowID_ || windowID_.value() == event.key.windowID)) {
			events_.push_back(event);
			processEvent(event);
		}
	}
}

void KeyboardEvents::processEvent(const SDL_Event event) {
	if (EventIs(event, SDL_KEYDOWN, SDL_KEYUP)) {
		auto key = event.key;
		keyStates[key.keysym.sym] = KeyState(
			key.state == SDL_PRESSED,
			key.repeat != 0,
			static_cast<SDL_Keymod>(key.keysym.mod));
	}
}

Optional<KeyState> KeyboardEvents::GetKeyState(const SDL_Keycode keyCode) const {
	auto keyState = keyStates.find(keyCode);

	if (keyState != keyStates.end()) {
		return keyState->second;
	} else {
		return Optional<KeyState>();
	}
}

const EventList& KeyboardEvents::GetEventList() const {
	return events_;
}

Optional<WindowIdForEvent> KeyboardEvents::GetWindowId() const {
	return windowID_;
}

}
