#include "ArrowsButton.h"
#include "Window.h"
#include "Logger.h"

ArrowsButton::ArrowsButton(int x, int y, Orientation orientation) : Component(x, y), orientation(orientation) {
	if (orientation == Orientation::VERTICAL) {
		width = 13;
		height = 27;
	} else if (orientation == Orientation::HORIZONTAL) {
		width = 13 * 2;
		height = 13;
	}
}

void ArrowsButton::draw(PK2::Engine::GFX& gfx) {
	if (orientation == Orientation::VERTICAL) {
		SDL_Rect destRect = { x, y, width, height };

		gfx.drawImage(Window::getEditorImageFile(), VERTICAL_CROP, destRect);
	} else if (orientation == Orientation::HORIZONTAL) {
		SDL_Rect destUp = { x, y, width / 2, height};
		SDL_Rect destDown = { x + 1 + width / 2, y, width / 2, height };

		gfx.drawImage(Window::getEditorImageFile(), HORIZONTAL_CROP_UP, destUp);
		gfx.drawImage(Window::getEditorImageFile(), HORIZONTAL_CROP_DOWN, destDown);
	}
}

void ArrowsButton::onClick(int mouseX, int mouseY, int mouseButton) {
	using Input = PK2::Engine::Input;

	if (mouseButton == Input::MB_LEFT) {
		if (orientation == Orientation::VERTICAL) {

			if (mouseY < y + height / 2) {
				if (scrollUpAction) scrollUpAction();
			} else {
				if (scrollDownAction) scrollDownAction();
			}

			Window::setResponseDelay(RESPONSE_DELAY);
		} else if (orientation == Orientation::HORIZONTAL) {
			if (mouseX < x + width / 2) {
				if (scrollUpAction) scrollUpAction();
			} else {
				if (scrollDownAction) scrollDownAction();
			}

			Window::setResponseDelay(RESPONSE_DELAY);
		}
	}
}

void ArrowsButton::setScrollUpAction(std::function<void()> function) {
	scrollUpAction = function;
}

void ArrowsButton::setScrollDownAction(std::function<void()> function) {
	scrollDownAction = function;
}