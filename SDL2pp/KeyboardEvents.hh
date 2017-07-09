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

#ifndef SDL2PP_KEYBOARDEVENTS_HH
#define SDL2PP_KEYBOARDEVENTS_HH

#include <SDL2pp/Export.hh>
#include <SDL2pp/EventUtils.hh>
#include <SDL2pp/KeyState.hh>
#include <SDL2pp/Optional.hh>

#include <unordered_map>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief Object representing a list of events for a given window (if any)
///
/// \ingroup event
///
/// \headerfile SDL2pp/KeyboardEvents.hh
///
/// This class filters the information of a list of events searching for keyboard
/// related events, then these events are processed and the relevant information
/// is stored for quick access using any of the member functions
///
/// \see https://wiki.libsdl.org/SDL_KeyboardEvent
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT KeyboardEvents {
private:
	Optional<WindowIdForEvent> windowID_;

	EventList events_;
	
	std::unordered_map<SDL_Keycode, KeyState> keyStates;
	
	void processEvents(const EventList events);
	
	void processEvent(const SDL_Event event);

public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates an empty object: no window id, no events, no key states
	///
	////////////////////////////////////////////////////////////
	KeyboardEvents();
	
	////////////////////////////////////////////////////////////
	/// \brief Construct a keyboard events object from a list of events
	///
	/// Creates an object by filtering all the keyboard states from the
	/// given list of states, any other events are ignored, the window id is
	/// also ignored
	///
	/// \param[in] events A list of SDL_Events to filter
	///
	////////////////////////////////////////////////////////////
	KeyboardEvents(const EventList events);
	
	////////////////////////////////////////////////////////////
	/// \brief Construct a keyboard events object from a list of events for a given window
	///
	/// Creates an object by filtering all the keyboard events from the
	/// given list of events for the given window, any other events are ignored
	///
	/// \param[in] windowID The id of the window
	/// \param[in] events A list of SDL_Events to filter
	///
	////////////////////////////////////////////////////////////
	KeyboardEvents(WindowIdForEvent windowID, const EventList events);
	
	////////////////////////////////////////////////////////////
	/// \brief Retrieves the key state for the given key code
	///
	/// Retrieves the key state for the given key code, if no events for the given
	/// keycode were processed in this keyboard state an empty optional is returned
	///
	/// \param[in] keyCode The key code of the key state to serach
	///
	/// \returns An optional with the key state if the key code was found,
	///          an empty optional otherwise
	///
	////////////////////////////////////////////////////////////
	Optional<KeyState> GetKeyState(const SDL_Keycode keyCode) const;
	
	////////////////////////////////////////////////////////////
	/// \brief Returns the list of events that this keyboard state represents
	///
	/// \returns The list of events this state represents
	///
	////////////////////////////////////////////////////////////
	const EventList& GetEventList() const;
	
	////////////////////////////////////////////////////////////
	/// \brief Returns the window id, if any
	///
	/// \returns The window id, if any
	///
	////////////////////////////////////////////////////////////
	Optional<WindowIdForEvent> GetWindowId() const;
};

}

#endif
