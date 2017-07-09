#include <SDL_main.h>

#include <SDL2pp/KeyState.hh>

#include "testing.h"

using namespace SDL2pp;
using namespace std;

BEGIN_TEST(int, char*[])
	// Test empty key state
	{
		KeyState emptyKeyState;
		EXPECT_TRUE(!emptyKeyState.IsPressed());
		EXPECT_TRUE(!emptyKeyState.IsRepeat());
		EXPECT_EQUAL(emptyKeyState.GetModifier(), KMOD_NONE);
	}

	// Test not empty key state
	{
		KeyState keyState(true, true, KMOD_CAPS);
		EXPECT_TRUE(keyState.IsPressed());
		EXPECT_TRUE(keyState.IsRepeat());
		EXPECT_EQUAL(keyState.GetModifier(), KMOD_CAPS);
	}

	// Test comparision operators
	{
		EXPECT_TRUE(KeyState() == KeyState());
		EXPECT_TRUE(KeyState(false, true, KMOD_CAPS) == KeyState(false, true, KMOD_CAPS));
		
		EXPECT_TRUE(KeyState() != KeyState(false, false, KMOD_RCTRL));
		EXPECT_TRUE(KeyState(false, true, KMOD_NUM) != KeyState(false, true, KMOD_RALT));
	}
END_TEST()
