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

void EventHandler::HandleEvent(const SDL_Event& event) {
	switch (event.type) {
	case SDL_QUIT:
		OnQuit(event.quit);
		break;
	case SDL_WINDOWEVENT:
		OnWindowEvent(event.window);
		break;
	case SDL_SYSWMEVENT:
		OnWindowManagerEvent(event.syswm);
		break;
	case SDL_KEYDOWN:
		OnKeyDown(event.key);
		break;
	case SDL_KEYUP:
		OnKeyUp(event.key);
		break;
	case SDL_TEXTEDITING:
		OnTextInput(event.text);
		break;
	case SDL_TEXTINPUT:
		OnTextEditing(event.edit);
		break;
	case SDL_MOUSEMOTION:
		OnMouseMotion(event.motion);
		break;
	case SDL_MOUSEBUTTONDOWN:
		OnMouseButtonDown(event.button);
		break;
	case SDL_MOUSEBUTTONUP:
		OnMouseButtonUp(event.button);
		break;
	case SDL_MOUSEWHEEL:
		OnMouseWheel(event.wheel);
		break;
	case SDL_JOYAXISMOTION:
		OnJoyAxisMotion(event.jaxis);
		break;
	case SDL_JOYBALLMOTION:
		OnJoyBallMotion(event.jball);
		break;
	case SDL_JOYHATMOTION:
		OnJoyHatMotion(event.jhat);
		break;
	case SDL_JOYBUTTONDOWN:
		OnJoyButtonDown(event.jbutton);
		break;
	case SDL_JOYBUTTONUP:
		OnJoyButtonUp(event.jbutton);
		break;
	case SDL_JOYDEVICEADDED:
		OnJoyDeviceAdded(event.jdevice);
		break;
	case SDL_JOYDEVICEREMOVED:
		OnJoyDeviceRemoved(event.jdevice);
		break;
	case SDL_CONTROLLERAXISMOTION:
		OnControllerAxisMotion(event.caxis);
		break;
	case SDL_CONTROLLERBUTTONDOWN:
		OnControllerButtonDown(event.cbutton);
		break;
	case SDL_CONTROLLERBUTTONUP:
		OnControllerButtonUp(event.cbutton);
		break;
	case SDL_CONTROLLERDEVICEADDED:
		OnControllerDeviceAdded(event.cdevice);
		break;
	case SDL_CONTROLLERDEVICEREMOVED:
		OnControllerDeviceRemoved(event.cdevice);
		break;
	case SDL_CONTROLLERDEVICEREMAPPED:
		OnControllerDeviceRemapped(event.cdevice);
		break;
	case SDL_USEREVENT:
		OnUserEvent(event.user);
		break;
	}
}

bool EventHandler::PollOneEvent() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		HandleEvent(event);
		return true;
	} else {
		return false;
	}
}

bool EventHandler::PollAllEvents() {
	bool eventHandled = false;
	
	while (PollOneEvent()) {
		eventHandled = true;
	}
	
	return eventHandled;
}

}
