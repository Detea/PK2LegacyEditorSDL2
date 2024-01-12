#include "Link.h"
#include "Window.h"

#include <iostream>

Link::Link(const std::string& text, int x, int y) : Component(x, y), text(text) {
	width = 200; // Should be text.length() * font.getAttributes().getLetterWidth(), but it's hardcoded to be 200 in the original code
	height = 8;
}

Link::~Link() {

}

void Link::onClick(int mouseX, int mouseY, int mouseButton) {
	if (visible) {
		if (Window::getResponseDelay() == 0) {
			if (action) {
				action();

				Window::setResponseDelay(RESPONSE_DELAY);
			}
		}
	}
}

void Link::onMouseOver(int mouseX, int mouseY) {
	if (positionInBounds(mouseX, mouseY)) {
		mouseOver = true;
	} else {
		mouseOver = false;
	}
}

void Link::draw(PK2::Engine::GFX& gfx) {
	if (visible) {
		if (mouseOver) {
			SDL_Color col = gfx.getColorInBackgroundPalette(COLOR_MOUSE_OVER);

			gfx.fillRect(x, y, width, height, col);
		}

		gfx.drawStringTransparent(text, x, y, 90);
	}
}

void Link::setAction(std::function<void()> function) {
	this->action = function;
}

void Link::setText(std::string_view text) {
	this->text = text;
}