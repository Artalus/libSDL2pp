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

#ifndef SDL2PP_EVENTMANAGER_HH
#define SDL2PP_EVENTMANAGER_HH

#include <SDL2pp/Export.hh>
#include <SDL2pp/EventUtils.hh>
#include <SDL2pp/KeyboardEvents.hh>
#include <SDL2pp/Optional.hh>

#include <map>

namespace SDL2pp {

class SDL2PP_EXPORT EventManager {
private:
	EventList events;
	
	// Caches are mutable because they don't affect the manager directly
	// the real ummutable value is events, caches are disposables
	
	mutable Optional<bool> quitEventCache;
	// for all events for all the windows
	mutable Optional<KeyboardEvents> keyboardEventsCache;
	// to store each event by window
	mutable std::map<WindowIdForEvent, KeyboardEvents> keyboardEventsCacheByWindow;
	
public:
	void CaptureEvents();
	
	KeyboardEvents GetKeyboardEvents() const;
	
	KeyboardEvents GetKeyboardEvents(WindowIdForEvent windowId) const;
	
	bool QuitEventCaptured() const;
	
	EventList GetCapturedEvents() const;
};

}

#endif
