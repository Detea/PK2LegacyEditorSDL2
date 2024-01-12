#pragma once
#include <SDL.h>

/*
	To update the keys place following code in the main loop:
		PK2::Engine::Input::updateKeymod(SDL_GetModState());
		PK2::Engine::Input::keyStates = SDL_GetKeyboardState(nullptr);

	To update the mouse:
		Uint32 mouseButton = SDL_GetMouseState(Input::getMouseXPointer(), Input::getMouseYPointer());
		Input::updateMouseButton(mouseButton);
*/
namespace PK2::Engine {
	class Input {
	public:
		static constexpr int MB_LEFT = 1;
		static constexpr int MB_MIDDLE = 2;
		static constexpr int MB_RIGHT = 3;
		
		// TODO These should be const, but that messes something up with the constructor and I have no idea why. Need to look into it.
		inline static SDL_Scancode KEY_NONE = SDL_Scancode::SDL_SCANCODE_UNKNOWN;
		inline static SDL_Keymod MOD_NONE = SDL_Keymod::KMOD_NONE;

		inline static const Uint8* keyStates = nullptr;

		// These two methods are used to set the mouse position with SDL2. Use the regular versions, if you want to get the mouse position.
		static int* getMouseXPointer();
		static int* getMouseYPointer();

		static int getMouseX();
		static int getMouseY();

		static void updateMouseButton(Uint32 buttonMask);
	
		static bool mouseDown(int button);

		// Returns true if either the left, middle or right mouse button is down
		static bool anyMouseDown();

		static bool keyPressed(SDL_Scancode scancode);
		static bool keyPressed(SDL_Scancode key, SDL_Keymod modifier);

		static void updateKeymod(SDL_Keymod mod);

		static void setTypedChar(char c);
		static char getTypedChar();
	private:
		inline static SDL_Keymod keymod = SDL_Keymod::KMOD_NONE;
		inline static int mouseButton = 0;

		inline static int mouseX = 0;
		inline static int mouseY = 0;

		inline static char typedChar = 0;
	};
}
