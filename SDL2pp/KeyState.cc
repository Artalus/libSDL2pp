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

#include <SDL2pp/KeyState.hh>

namespace SDL2pp {

KeyState::KeyState() : KeyState(false, false, KMOD_NONE) {
}

KeyState::KeyState(bool pressed, bool repeat, SDL_Keymod modifier) : pressed_(pressed), repeat_(repeat), modifier_(modifier) {
}

bool KeyState::IsPressed() const {
	return pressed_;
}

bool KeyState::IsRepeat() const {
	return repeat_;
}

SDL_Keymod KeyState::GetModifier() const {
	return modifier_;
}

}

bool operator==(const SDL2pp::KeyState& a, const SDL2pp::KeyState& b) {
	return a.IsPressed() == b.IsPressed() && a.IsRepeat() == b.IsRepeat()
		&& a.GetModifier() == b.GetModifier();
}

bool operator!=(const SDL2pp::KeyState& a, const SDL2pp::KeyState& b) {
	return !(a == b);
}

std::string GetKeyModName(const SDL_Keymod& keymod) {
	if (KMOD_NONE == keymod) { return "NONE"; }
	else if (KMOD_LSHIFT == keymod) { return "LSHIFT"; }
	else if (KMOD_RSHIFT == keymod) { return "RSHIFT"; }
	else if (KMOD_LCTRL == keymod) { return "LCTRL"; }
	else if (KMOD_RCTRL == keymod) { return "RCTRL"; }
	else if (KMOD_LALT == keymod) { return "LALT"; }
	else if (KMOD_RALT == keymod) { return "RALT"; }
	else if (KMOD_LGUI == keymod) { return "LGUI"; }
	else if (KMOD_RGUI == keymod) { return "RGUI"; }
	else if (KMOD_NUM == keymod) { return "NUM"; }
	else if (KMOD_CAPS == keymod) { return "CAPS"; }
	else if (KMOD_MODE == keymod) { return "MODE"; }
	else if (KMOD_RESERVED == keymod) { return "RESERVED"; }
	else if (KMOD_CTRL == keymod) { return "CTRL"; }
	else if (KMOD_SHIFT == keymod) { return "SHIFT"; }
	else if (KMOD_ALT == keymod) { return "ALT"; }
	else if (KMOD_GUI == keymod) { return "GUI"; }
	else { return ""; }
}

std::ostream& operator<<(std::ostream& stream, const SDL2pp::KeyState& keyState) {
	stream << "[pressed:" << keyState.IsPressed() << ",repeat:" << keyState.IsPressed();
	stream << ",mod:" << GetKeyModName(keyState.GetModifier()) << "]";
	return stream;
}
