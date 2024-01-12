#include "Button.h"
#include "Input.h"
#include "Window.h"

Button::Button(const std::string& text) : Button(text, 0, 0) {

}

Button::Button(const std::string& text, int x, int y) : Component(x, y), text(text) {
	int labelWidth = font.getFontAttributes().getLetterWidth() * text.length();

	width = labelWidth + 2;
	height = 12;
}

void Button::draw(PK2::Engine::GFX& gfx) {
	if (visible) {
		SDL_Color col = gfx.getColorInBackgroundPalette(borderColor);
		SDL_Color backBorderCol = gfx.getColorInBackgroundPalette(0);

		gfx.drawString(text, x + LABEL_OFFSET_X, y + LABEL_OFFSET_Y);

		gfx.drawRect(x + 1, y + 1, width, height, backBorderCol);
		gfx.drawRect(x, y, width, height, col);
	}
}

void Button::onMouseOver(int mouseX, int mouseY) {
	if (positionInBounds(mouseX, mouseY)) {
		borderColor = colorClicked; // TODO Rename this variable to colorHighlighted
	} else {
		borderColor = color;
	}
}

void Button::onClick(int clickX, int clickY, int mouseButton) {
	if (Window::getResponseDelay() == 0) {
		if (mouseButton == PK2::Engine::Input::MB_LEFT) {
			Window::setResponseDelay(RESPONSE_DELAY);

			if (action) action();
		}
	}
}

void Button::setAction(std::function<void()> a) {
	action = a;
}

void Button::setText(std::string_view newText) {
	text = newText;
	
	width = font.getFontAttributes().getLetterWidth() * text.length() + 2;
}