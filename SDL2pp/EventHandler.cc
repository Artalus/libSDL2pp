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

void EventHandler::OnQuit(const SDL_QuitEvent&) { }

void EventHandler::OnWindowEvent(const SDL_WindowEvent&) { }

void EventHandler::OnWindowManagerEvent(const SDL_SysWMEvent&) { }

void EventHandler::OnKeyDown(const SDL_KeyboardEvent&) { }

void EventHandler::OnKeyUp(const SDL_KeyboardEvent&) { }

void EventHandler::OnTextEditing(const SDL_TextEditingEvent&) { }

void EventHandler::OnTextInput(const SDL_TextInputEvent&) { }

void EventHandler::OnMouseMotion(const SDL_MouseMotionEvent&) { }

void EventHandler::OnMouseButtonDown(const SDL_MouseButtonEvent&) { }

void EventHandler::OnMouseButtonUp(const SDL_MouseButtonEvent&) { }

void EventHandler::OnMouseWheel(const SDL_MouseWheelEvent&) { }

void EventHandler::OnJoyAxisMotion(const SDL_JoyAxisEvent&) { }

void EventHandler::OnJoyBallMotion(const SDL_JoyBallEvent&) { }

void EventHandler::OnJoyHatMotion(const SDL_JoyHatEvent&) { }

void EventHandler::OnJoyButtonDown(const SDL_JoyButtonEvent&) { }

void EventHandler::OnJoyButtonUp(const SDL_JoyButtonEvent&) { }

void EventHandler::OnJoyDeviceAdded(const SDL_JoyDeviceEvent&) { }

void EventHandler::OnJoyDeviceRemoved(const SDL_JoyDeviceEvent&) { }

void EventHandler::OnControllerAxisMotion(const SDL_ControllerAxisEvent&) { }

void EventHandler::OnControllerButtonDown(const SDL_ControllerButtonEvent&) { }

void EventHandler::OnControllerButtonUp(const SDL_ControllerButtonEvent&) { }

void EventHandler::OnControllerDeviceAdded(const SDL_ControllerDeviceEvent&) { }

void EventHandler::OnControllerDeviceRemoved(const SDL_ControllerDeviceEvent&) { }

void EventHandler::OnControllerDeviceRemapped(const SDL_ControllerDeviceEvent&) { }

void EventHandler::OnUserEvent(const SDL_UserEvent&) { }

void EventHandler::HandleEvent(SDL_Event event) {
	if (SDL_QUIT == event.type) { OnQuit(event.quit); }
	else if (SDL_WINDOWEVENT == event.type) { OnWindowEvent(event.window); }
	else if (SDL_SYSWMEVENT == event.type) { OnWindowManagerEvent(event.syswm); }
	else if (SDL_KEYDOWN == event.type) { OnKeyDown(event.key); }
	else if (SDL_KEYUP == event.type) { OnKeyUp(event.key); }
	else if (SDL_TEXTEDITING == event.type) { OnTextInput(event.text); }
	else if (SDL_TEXTINPUT == event.type) { OnTextEditing(event.edit); }
	else if (SDL_MOUSEMOTION == event.type) { OnMouseMotion(event.motion); }
	else if (SDL_MOUSEBUTTONDOWN == event.type) { OnMouseButtonDown(event.button); }
	else if (SDL_MOUSEBUTTONUP == event.type) { OnMouseButtonUp(event.button); }
	else if (SDL_MOUSEWHEEL == event.type) { OnMouseWheel(event.wheel); }
	else if (SDL_JOYAXISMOTION == event.type) { OnJoyAxisMotion(event.jaxis); }
	else if (SDL_JOYBALLMOTION == event.type) { OnJoyBallMotion(event.jball); }
	else if (SDL_JOYHATMOTION == event.type) { OnJoyHatMotion(event.jhat); }
	else if (SDL_JOYBUTTONDOWN == event.type) { OnJoyButtonDown(event.jbutton); }
	else if (SDL_JOYBUTTONUP == event.type) { OnJoyButtonUp(event.jbutton); }
	else if (SDL_JOYDEVICEADDED == event.type) { OnJoyDeviceAdded(event.jdevice); }
	else if (SDL_JOYDEVICEREMOVED == event.type) { OnJoyDeviceRemoved(event.jdevice); }
	else if (SDL_CONTROLLERAXISMOTION == event.type) { OnControllerAxisMotion(event.caxis); }
	else if (SDL_CONTROLLERBUTTONDOWN == event.type) { OnControllerButtonDown(event.cbutton); }
	else if (SDL_CONTROLLERBUTTONUP == event.type) { OnControllerButtonUp(event.cbutton); }
	else if (SDL_CONTROLLERDEVICEADDED == event.type) { OnControllerDeviceAdded(event.cdevice); }
	else if (SDL_CONTROLLERDEVICEREMOVED == event.type) { OnControllerDeviceRemoved(event.cdevice); }
	else if (SDL_CONTROLLERDEVICEREMAPPED == event.type) { OnControllerDeviceRemapped(event.cdevice); }
	else if (SDL_USEREVENT == event.type) { OnUserEvent(event.user); }
}

Optional<SDL_Event> EventHandler::PollOneEvent() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		HandleEvent(event);
		return event;
	} else {
		return Optional<SDL_Event>();
	}
}

vector<SDL_Event> EventHandler::PollAllEvents() {
	vector<SDL_Event> events;
	
	// One liner to PollOneEvent and add it to the vector
	// until there is no more events to poll
	for (Optional<SDL_Event> event;
		(event = PollOneEvent());
		events.push_back(*event));
	
	return events;
}

}
