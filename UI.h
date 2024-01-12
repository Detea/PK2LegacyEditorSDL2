#pragma once

#include <vector>

#include "Window.h"
#include "GFX.h"

class UI {
public:
	UI();
	~UI();

	void addWindow(Window* w);

	void updateMouse(int mouseX, int mouseY);
	void updateKeyboard(SDL_Scancode key, SDL_Keymod modifier);

	virtual void onKeyTyped(char c);

	void render(PK2::Engine::GFX& gfx);

private:
	// Sets the active window, when the user clicks on a windows title bar, marks it grabbed and handles closing the window.
	void handleTitlebar(Window* window, int clickX, int clickY);

private:
	std::vector<Window*> windows;

	// Contains the currently active window, points to one of the Window in the windows vector.
	Window* activeWindow = nullptr;
};