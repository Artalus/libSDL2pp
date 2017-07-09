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

#include <SDL2pp/EventUtils.hh>

using std::string;

namespace SDL2pp {
	bool EventIs(const SDL_Event event, const SDL_EventType type) {
		return event.type == type;
	}

	string GetEventName(const SDL_Event event) {
		if (SDL_APP_DIDENTERBACKGROUND == event.type) { return "APP_DIDENTERBACKGROUND"; }
		else if (SDL_APP_DIDENTERFOREGROUND == event.type) { return "APP_DIDENTERFOREGROUND"; }
		else if (SDL_APP_LOWMEMORY == event.type) { return "APP_LOWMEMORY"; }
		else if (SDL_APP_TERMINATING == event.type) { return "APP_TERMINATING"; }
		else if (SDL_APP_WILLENTERBACKGROUND == event.type) { return "APP_WILLENTERBACKGROUND"; }
		else if (SDL_APP_WILLENTERFOREGROUND == event.type) { return "APP_WILLENTERFOREGROUND"; }
		else if (SDL_AUDIODEVICEADDED == event.type) { return "AUDIODEVICEADDED"; }
		else if (SDL_AUDIODEVICEREMOVED == event.type) { return "AUDIODEVICEREMOVED"; }
		else if (SDL_CLIPBOARDUPDATE == event.type) { return "CLIPBOARDUPDATE"; }
		else if (SDL_CONTROLLERAXISMOTION == event.type) { return "CONTROLLERAXISMOTION"; }
		else if (SDL_CONTROLLERBUTTONDOWN == event.type) { return "CONTROLLERBUTTONDOWN"; }
		else if (SDL_CONTROLLERBUTTONUP == event.type) { return "CONTROLLERBUTTONUP"; }
		else if (SDL_CONTROLLERDEVICEADDED == event.type) { return "CONTROLLERDEVICEADDED"; }
		else if (SDL_CONTROLLERDEVICEREMAPPED == event.type) { return "CONTROLLERDEVICEREMAPPED"; }
		else if (SDL_CONTROLLERDEVICEREMOVED == event.type) { return "CONTROLLERDEVICEREMOVED"; }
		else if (SDL_DOLLARGESTURE == event.type) { return "DOLLARGESTURE"; }
		else if (SDL_DOLLARRECORD == event.type) { return "DOLLARRECORD"; }
		else if (SDL_DROPBEGIN == event.type) { return "DROPBEGIN"; }
		else if (SDL_DROPCOMPLETE == event.type) { return "DROPCOMPLETE"; }
		else if (SDL_DROPFILE == event.type) { return "DROPFILE"; }
		else if (SDL_DROPTEXT == event.type) { return "DROPTEXT"; }
		else if (SDL_FINGERDOWN == event.type) { return "FINGERDOWN"; }
		else if (SDL_FINGERMOTION == event.type) { return "FINGERMOTION"; }
		else if (SDL_FINGERUP == event.type) { return "FINGERUP"; }
		else if (SDL_FIRSTEVENT == event.type) { return "FIRSTEVENT"; }
		else if (SDL_JOYAXISMOTION == event.type) { return "JOYAXISMOTION"; }
		else if (SDL_JOYBALLMOTION == event.type) { return "JOYBALLMOTION"; }
		else if (SDL_JOYBUTTONDOWN == event.type) { return "JOYBUTTONDOWN"; }
		else if (SDL_JOYBUTTONUP == event.type) { return "JOYBUTTONUP"; }
		else if (SDL_JOYDEVICEADDED == event.type) { return "JOYDEVICEADDED"; }
		else if (SDL_JOYDEVICEREMOVED == event.type) { return "JOYDEVICEREMOVED"; }
		else if (SDL_JOYHATMOTION == event.type) { return "JOYHATMOTION"; }
		else if (SDL_KEYDOWN == event.type) { return "KEYDOWN"; }
		else if (SDL_KEYMAPCHANGED == event.type) { return "KEYMAPCHANGED"; }
		else if (SDL_KEYUP == event.type) { return "KEYUP"; }
		else if (SDL_LASTEVENT == event.type) { return "LASTEVENT"; }
		else if (SDL_MOUSEBUTTONDOWN == event.type) { return "MOUSEBUTTONDOWN"; }
		else if (SDL_MOUSEBUTTONUP == event.type) { return "MOUSEBUTTONUP"; }
		else if (SDL_MOUSEMOTION == event.type) { return "MOUSEMOTION"; }
		else if (SDL_MOUSEWHEEL == event.type) { return "MOUSEWHEEL"; }
		else if (SDL_MULTIGESTURE == event.type) { return "MULTIGESTURE"; }
		else if (SDL_QUIT == event.type) { return "QUIT"; }
		else if (SDL_RENDER_DEVICE_RESET == event.type) { return "RENDER_DEVICE_RESET"; }
		else if (SDL_RENDER_TARGETS_RESET == event.type) { return "RENDER_TARGETS_RESET"; }
		else if (SDL_SYSWMEVENT == event.type) { return "SYSWMEVENT"; }
		else if (SDL_TEXTEDITING == event.type) { return "TEXTEDITING"; }
		else if (SDL_TEXTINPUT == event.type) { return "TEXTINPUT"; }
		else if (SDL_USEREVENT == event.type) { return "USEREVENT"; }
		else if (SDL_WINDOWEVENT == event.type) { return "WINDOWEVENT"; }
		else { return ""; }
	}
}
