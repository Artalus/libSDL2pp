#include <SDL_main.h>

#include <SDL2pp/EventHandler.hh>

#include "testing.h"

using namespace SDL2pp;

class TestEventHandler : public EventHandler {
private:
	bool quitEvent_ = false;
	bool windowEventEvent_ = false;
	bool hasWindowManagerEventEvent_ = false;
	bool keyDownEvent_ = false;
	bool keyUpEvent_ = false;
	bool textEditingEvent_ = false;
	bool textInputEvent_ = false;
	bool mouseMotionEvent_ = false;
	bool mouseButtonDownEvent_ = false;
	bool mouseButtonUpEvent_ = false;
	bool mouseWheelEvent_ = false;
	bool joyAxisMotionEvent_ = false;
	bool joyBallMotionEvent_ = false;
	bool joyHatMotionEvent_ = false;
	bool joyButtonDownEvent_ = false;
	bool joyButtonUpEvent_ = false;
	bool joyDeviceAddedEvent_ = false;
	bool joyDeviceRemovedEvent_ = false;
	bool controllerAxisMotionEvent_ = false;
	bool controllerButtonDownEvent_ = false;
	bool controllerButtonUpEvent_ = false;
	bool controllerDeviceAddedEvent_ = false;
	bool controllerDeviceRemovedEvent_ = false;
	bool controllerDeviceRemappedEvent_ = false;
	bool userEventEvent_ = false;

protected:
	void OnQuit(SDL_QuitEvent) override { quitEvent_ = true; }
	void OnWindowEvent(SDL_WindowEvent) override { windowEventEvent_ = true; }
	void OnWindowManagerEvent(SDL_SysWMEvent) override { hasWindowManagerEventEvent_ = true; }
	void OnKeyDown(SDL_KeyboardEvent) override { keyDownEvent_ = true; }
	void OnKeyUp(SDL_KeyboardEvent) override { keyUpEvent_ = true; }
	void OnTextEditing(SDL_TextEditingEvent) override { textEditingEvent_ = true; }
	void OnTextInput(SDL_TextInputEvent) override { textInputEvent_ = true; }
	void OnMouseMotion(SDL_MouseMotionEvent) override { mouseMotionEvent_ = true; }
	void OnMouseButtonDown(SDL_MouseButtonEvent) override { mouseButtonDownEvent_ = true; }
	void OnMouseButtonUp(SDL_MouseButtonEvent) override { mouseButtonUpEvent_ = true; }
	void OnMouseWheel(SDL_MouseWheelEvent) override { mouseWheelEvent_ = true; }
	void OnJoyAxisMotion(SDL_JoyAxisEvent) override { joyAxisMotionEvent_ = true; }
	void OnJoyBallMotion(SDL_JoyBallEvent) override { joyBallMotionEvent_ = true; }
	void OnJoyHatMotion(SDL_JoyHatEvent) override { joyHatMotionEvent_ = true; }
	void OnJoyButtonDown(SDL_JoyButtonEvent) override { joyButtonDownEvent_ = true; }
	void OnJoyButtonUp(SDL_JoyButtonEvent) override { joyButtonUpEvent_ = true; }
	void OnJoyDeviceAdded(SDL_JoyDeviceEvent) override { joyDeviceAddedEvent_ = true; }
	void OnJoyDeviceRemoved(SDL_JoyDeviceEvent) override { joyDeviceRemovedEvent_ = true; }
	void OnControllerAxisMotion(SDL_ControllerAxisEvent) override { controllerAxisMotionEvent_ = true; }
	void OnControllerButtonDown(SDL_ControllerButtonEvent) override { controllerButtonDownEvent_ = true; }
	void OnControllerButtonUp(SDL_ControllerButtonEvent) override { controllerButtonUpEvent_ = true; }
	void OnControllerDeviceAdded(SDL_ControllerDeviceEvent) override { controllerDeviceAddedEvent_ = true; }
	void OnControllerDeviceRemoved(SDL_ControllerDeviceEvent) override { controllerDeviceRemovedEvent_ = true; }
	void OnControllerDeviceRemapped(SDL_ControllerDeviceEvent) override { controllerDeviceRemappedEvent_ = true; }
	void OnUserEvent(SDL_UserEvent) override { userEventEvent_ = true; }

public:
	bool HasQuitEvent() const { return quitEvent_; }
	bool HasWindowEventEvent() const { return windowEventEvent_; }
	bool HasWindowManagerEventEvent() const { return hasWindowManagerEventEvent_; }
	bool HasKeyDownEvent() const { return keyDownEvent_; }
	bool HasKeyUpEvent() const { return keyUpEvent_; }
	bool HasTextEditingEvent() const { return textEditingEvent_; }
	bool HasTextInputEvent() const { return textInputEvent_; }
	bool HasMouseMotionEvent() const { return mouseMotionEvent_; }
	bool HasMouseButtonDownEvent() const { return mouseButtonDownEvent_; }
	bool HasMouseButtonUpEvent() const { return mouseButtonUpEvent_; }
	bool HasMouseWheelEvent() const { return mouseWheelEvent_; }
	bool HasJoyAxisMotionEvent() const { return joyAxisMotionEvent_; }
	bool HasJoyBallMotionEvent() const { return joyBallMotionEvent_; }
	bool HasJoyHatMotionEvent() const { return joyHatMotionEvent_; }
	bool HasJoyButtonDownEvent() const { return joyButtonDownEvent_; }
	bool HasJoyButtonUpEvent() const { return joyButtonUpEvent_; }
	bool HasJoyDeviceAddedEvent() const { return joyDeviceAddedEvent_; }
	bool HasJoyDeviceRemovedEvent() const { return joyDeviceRemovedEvent_; }
	bool HasControllerAxisMotionEvent() const { return controllerAxisMotionEvent_; }
	bool HasControllerButtonDownEvent() const { return controllerButtonDownEvent_; }
	bool HasControllerButtonUpEvent() const { return controllerButtonUpEvent_; }
	bool HasControllerDeviceAddedEvent() const { return controllerDeviceAddedEvent_; }
	bool HasControllerDeviceRemovedEvent() const { return controllerDeviceRemovedEvent_; }
	bool HasControllerDeviceRemappedEvent() const { return controllerDeviceRemappedEvent_; }
	bool HasUserEventEvent() const { return userEventEvent_; }
};

struct Test {
	using VerificationMethod = std::function<std::pair<bool, std::string>(TestEventHandler&)>;

	Test(SDL_EventType eventType, std::string eventName, VerificationMethod verificationMethod) :
		eventType(eventType),
		eventName(eventName),
		verificationMethod(verificationMethod)
	{
	}
	
	SDL_EventType eventType;
	std::string eventName;
	VerificationMethod verificationMethod;
};

#define TEST(eventName, verificationMethod) Test(eventName, #eventName, [](TestEventHandler& eventHandler) { return std::make_pair(eventHandler.verificationMethod(), #eventName); })

BEGIN_TEST(int, char*[])
	auto tests = std::vector<Test> {
		TEST(SDL_QUIT, HasQuitEvent),
		TEST(SDL_WINDOWEVENT, HasWindowEventEvent),
		//TEST(SDL_SYSWMEVENT, HasWindowManagerEventEvent),
		TEST(SDL_KEYDOWN, HasKeyDownEvent),
		TEST(SDL_KEYUP, HasKeyUpEvent),
		TEST(SDL_TEXTEDITING, HasTextInputEvent),
		TEST(SDL_TEXTINPUT, HasTextEditingEvent),
		TEST(SDL_MOUSEMOTION, HasMouseMotionEvent),
		TEST(SDL_MOUSEBUTTONDOWN, HasMouseButtonDownEvent),
		TEST(SDL_MOUSEBUTTONUP, HasMouseButtonUpEvent),
		TEST(SDL_MOUSEWHEEL, HasMouseWheelEvent),
		TEST(SDL_JOYAXISMOTION, HasJoyAxisMotionEvent),
		TEST(SDL_JOYBALLMOTION, HasJoyBallMotionEvent),
		TEST(SDL_JOYHATMOTION, HasJoyHatMotionEvent),
		TEST(SDL_JOYBUTTONDOWN, HasJoyButtonDownEvent),
		TEST(SDL_JOYBUTTONUP, HasJoyButtonUpEvent),
		TEST(SDL_JOYDEVICEADDED, HasJoyDeviceAddedEvent),
		TEST(SDL_JOYDEVICEREMOVED, HasJoyDeviceRemovedEvent),
		TEST(SDL_CONTROLLERAXISMOTION, HasControllerAxisMotionEvent),
		TEST(SDL_CONTROLLERBUTTONDOWN, HasControllerButtonDownEvent),
		TEST(SDL_CONTROLLERBUTTONUP, HasControllerButtonUpEvent),
		TEST(SDL_CONTROLLERDEVICEADDED, HasControllerDeviceAddedEvent),
		TEST(SDL_CONTROLLERDEVICEREMOVED, HasControllerDeviceRemovedEvent),
		TEST(SDL_CONTROLLERDEVICEREMAPPED, HasControllerDeviceRemappedEvent),
		TEST(SDL_USEREVENT, HasUserEventEvent)
	};

	for (auto& test : tests) {
		SDL_Event event;
		event.type = test.eventType;
		SDL_PushEvent(&event);
		
		auto eventHandler = TestEventHandler{};
		auto polledEvent = eventHandler.PollOneEvent();
		auto result = test.verificationMethod(eventHandler);
		
		EXPECT_EQUAL(test.eventName, test.eventName);
		EXPECT_TRUE(result.first);
		EXPECT_EQUAL(polledEvent->type, test.eventType);
	}
END_TEST()
