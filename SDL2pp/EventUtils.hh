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

#ifndef SDL2PP_EVENTUTILS_HH
#define SDL2PP_EVENTUTILS_HH

#include <SDL_events.h>
#include <SDL2pp/Export.hh>
#include <string>
#include <vector>

namespace SDL2pp {
	////////////////////////////////////////////////////////////
	/// \brief Alias for a list of SDL_Event
	///
	/// \ingroup event
	///
	/// \headerfile SDL2pp/EventUtils.hh
	///
	////////////////////////////////////////////////////////////
	using EventList = std::vector<SDL_Event>;
	
	////////////////////////////////////////////////////////////
	/// \brief Alias for a window id for a given event
	///
	/// \ingroup event
	///
	/// \headerfile SDL2pp/EventUtils.hh
	///
	////////////////////////////////////////////////////////////
	using WindowIdForEvent = Uint32;

	////////////////////////////////////////////////////////////
	/// \brief Function to identify if the given event is a given type
	///
	/// \ingroup event
	///
	/// \headerfile SDL2pp/EventUtils.hh
	///
	/// \param[in] event The event to identify
	/// \param[in] type The type to check for the event
	///
	/// \returns True if the event is of the given type
	///
	////////////////////////////////////////////////////////////
	SDL2PP_EXPORT bool EventIs(const SDL_Event event, const SDL_EventType type);

	////////////////////////////////////////////////////////////
	/// \brief Function to identify it the given event is a given list of types
	///
	/// \ingroup event
	///
	/// \headerfile SDL2pp/EventUtils.hh
	///
	/// \param[in] event The event to identify
	/// \param[in] type The type to check for the event
	/// \param[in] types List of types to check for the event
	///
	/// \returns True if the event is of any of the given types
	///
	////////////////////////////////////////////////////////////
	template <typename... EVENT_TYPES>
	SDL2PP_EXPORT bool EventIs(const SDL_Event event, const SDL_EventType type, EVENT_TYPES... types) {
		return EventIs(event, type) || EventIs(event, types...);
	}
	
	////////////////////////////////////////////////////////////
	/// \brief Returns a redeable string for the type of the given event
	///
	/// \ingroup event
	///
	/// \headerfile SDL2pp/EventUtils.hh
	///
	/// \param[in] event The event to identify
	///
	/// \returns A redeable string with the name of the event type or an empty string if the type is not identified
	///
	////////////////////////////////////////////////////////////
	SDL2PP_EXPORT std::string GetEventName(const SDL_Event event);
}

#endif
