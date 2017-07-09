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

#ifndef SDL2PP_KEYSTATE_HH
#define SDL2PP_KEYSTATE_HH

#include <SDL_events.h>

#include <SDL2pp/Export.hh>
#include <SDL2pp/Optional.hh>

#include <functional> // For std::hash
#include <ostream> // For output stream

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief Class representing the state of a key in a given moment
///
/// \ingroup event
///
/// \headerfile SDL2pp/KeyState.hh
///
/// \see https://wiki.libsdl.org/SDL_Keysym
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT KeyState {
private:
	bool pressed_;

	bool repeat_;

	SDL_Keymod modifier_;

public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates an empty key state (all false, no modifier)
	///
	////////////////////////////////////////////////////////////
	KeyState();

	////////////////////////////////////////////////////////////
	/// \brief Construct the key state from the given arguments
	///
	/// \param[in] pressed True if the key is pressed, false otherwise
	/// \param[in] repeat True if the key was pressed with repeate, false otherwise
	/// \param[in] modifier The modifier for the key
	///
	////////////////////////////////////////////////////////////
	KeyState(bool pressed, bool repeat, SDL_Keymod modifier);

	////////////////////////////////////////////////////////////
	/// \brief Checks if the key is pressed
	///
	/// \return True if the key is pressed, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool IsPressed() const;

	////////////////////////////////////////////////////////////
	/// \brief Checks if the key has been pressed repeatedly
	///
	/// \return True if the key was pressed repeatedly, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool IsRepeat() const;

	////////////////////////////////////////////////////////////
	/// \brief Gets the modifier for the key
	///
	/// \returns The modifier for the key
	///
	////////////////////////////////////////////////////////////
	SDL_Keymod GetModifier() const;
};

}

////////////////////////////////////////////////////////////
/// \brief Equality operator for SDL2pp::KeyState
///
/// \param[in] a First argument for comparison
/// \param[in] b Second argument for comparison
///
/// \returns True if two key states are identical
///
////////////////////////////////////////////////////////////
bool operator==(const SDL2pp::KeyState& a, const SDL2pp::KeyState& b);

////////////////////////////////////////////////////////////
/// \brief Inequality operator for SDL2pp::KeyState
///
/// \param[in] a First argument for comparison
/// \param[in] b Second argument for comparison
///
/// \returns True if two key states are not identical
///
////////////////////////////////////////////////////////////
bool operator!=(const SDL2pp::KeyState& a, const SDL2pp::KeyState& b);

////////////////////////////////////////////////////////////
/// \brief Stream output operator overload for SDL2pp::KeyState
///
/// \param[in] stream Stream to output to
/// \param[in] point Key state to output
///
/// \returns stream
///
////////////////////////////////////////////////////////////
SDL2PP_EXPORT std::ostream& operator<<(std::ostream& stream, const SDL2pp::KeyState& keyState);

////////////////////////////////////////////////////////////
/// \brief Function to get a redeable name for a given keymod
///
/// \ingroup event
///
/// \param[in] keymod The keymod to get a readable name
///
/// \returns A string with a redeable name for the keymod or empty if unkown
///
////////////////////////////////////////////////////////////
std::string GetKeyModName(const SDL_Keymod& keymod);

namespace std {

////////////////////////////////////////////////////////////
/// \brief std::hash specialization for SDL2pp::KeyState
///
////////////////////////////////////////////////////////////
template<>
struct hash<SDL2pp::KeyState> {
	////////////////////////////////////////////////////////////
	/// \brief Hash function for SDL2pp::KeyState
	///
	/// \param[in] keyState Input key state
	///
	/// \returns Hash value
	///
	////////////////////////////////////////////////////////////
	size_t operator()(const SDL2pp::KeyState& keyState) {
		size_t seed = std::hash<bool>()(keyState.IsPressed());
		seed ^= std::hash<bool>()(keyState.IsRepeat()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		seed ^= std::hash<int>()(keyState.GetModifier()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		return seed;
	}
};

}

#endif
