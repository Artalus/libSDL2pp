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

#ifndef SDL2PP_EVENTHANDLER_HH
#define SDL2PP_EVENTHANDLER_HH

#include <SDL_events.h>

#include <SDL2pp/Export.hh>
#include <SDL2pp/Optional.hh>

#include <vector>

namespace SDL2pp {

class SDL2PP_EXPORT EventHandler {
private:
	void HandleEvent(SDL_Event event);

protected:
	virtual void OnQuit(SDL_QuitEvent event);
	
	virtual void OnWindowEvent(SDL_WindowEvent event);
	
	virtual void OnWindowManagerEvent(SDL_SysWMEvent event);

	virtual void OnKeyDown(SDL_KeyboardEvent event);
	
	virtual void OnKeyUp(SDL_KeyboardEvent event);
	
	virtual void OnTextEditing(SDL_TextEditingEvent event);
	
	virtual void OnTextInput(SDL_TextInputEvent event);
	
	virtual void OnMouseMotion(SDL_MouseMotionEvent event);
	
	virtual void OnMouseButtonDown(SDL_MouseButtonEvent event);
	
	virtual void OnMouseButtonUp(SDL_MouseButtonEvent event);
	
	virtual void OnMouseWheel(SDL_MouseWheelEvent event);
	
	virtual void OnJoyAxisMotion(SDL_JoyAxisEvent event);
	
	virtual void OnJoyBallMotion(SDL_JoyBallEvent event);
	
	virtual void OnJoyHatMotion(SDL_JoyHatEvent event);
	
	virtual void OnJoyButtonDown(SDL_JoyButtonEvent event);
	
	virtual void OnJoyButtonUp(SDL_JoyButtonEvent event);
	
	virtual void OnJoyDeviceAdded(SDL_JoyDeviceEvent event);
	
	virtual void OnJoyDeviceRemoved(SDL_JoyDeviceEvent event);
	
	virtual void OnControllerAxisMotion(SDL_ControllerAxisEvent event);
	
	virtual void OnControllerButtonDown(SDL_ControllerButtonEvent event);
	
	virtual void OnControllerButtonUp(SDL_ControllerButtonEvent event);
	
	virtual void OnControllerDeviceAdded(SDL_ControllerDeviceEvent event);
	
	virtual void OnControllerDeviceRemoved(SDL_ControllerDeviceEvent event);
	
	virtual void OnControllerDeviceRemapped(SDL_ControllerDeviceEvent event);
	
	virtual void OnUserEvent(SDL_UserEvent event);
	
public:
	Optional<SDL_Event> PollOneEvent();
	
	std::vector<SDL_Event> PollAllEvents();
};

}

#endif
