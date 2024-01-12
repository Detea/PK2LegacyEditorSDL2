#pragma once
#include "Window.h"
#include "ArrowsButton.h"

class TestWindow : public Window {
public:
	TestWindow(std::string title,
			   int x, int y,
			   int width, int height,

			   bool visible,

			   SDL_Scancode shortcutKey = PK2::Engine::Input::KEY_NONE,
			   SDL_Keymod shortcutMod = PK2::Engine::Input::MOD_NONE);

	virtual ~TestWindow();

private:
	void setupUI();

private:
	ArrowsButton* arrowsVertical = nullptr;
	ArrowsButton* arrowsHorizontal = nullptr;
};

