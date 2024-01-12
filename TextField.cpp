#include "TextField.h"

#include "Window.h"

TextField::TextField(const std::string& text, int maxChars, int x, int y) : Component(x, y), maxChars(maxChars), text(text) {
	width = font.getFontAttributes().getLetterWidth() * maxChars;
	height = 10;
}

TextField::TextField(int maxChars, int x, int y) : TextField("", maxChars, x, y) {
}

void TextField::draw(PK2::Engine::GFX& gfx) {
	SDL_Color col = (editing && hasWindowFocus) ? gfx.getColorInBackgroundPalette(COLOR_ACTIVE) : gfx.getColorInBackgroundPalette(COLOR_INACTIVE);

	gfx.fillRect(x, y, width, height, col);

	if (editing && hasWindowFocus) {
		SDL_Color colCursor = gfx.getColorInBackgroundPalette(COLOR_CURSOR);
		gfx.fillRect(x + (cursorPos * CURSOR_WIDTH), y, CURSOR_WIDTH, CURSOR_HEIGHT, colCursor);
	}

	// TODO Draw transparent font value 85?
	gfx.drawString(text, x, y + 2);
}

void TextField::onClick(int mouseX, int mouseY, int mouseButton) {
	if (focused) {
		int cPos = (mouseX - x) / 8;
		if (cPos < text.length()) {
			cursorPos = cPos;
		} else {
			cursorPos = text.length();
		}

		Window::setResponseDelay(RESPONSE_DELAY);
	}
}

void TextField::onKeyDown(SDL_Scancode key, SDL_Keymod modifier) {
	if (editing && hasWindowFocus) {
		if (Window::getResponseDelay() == 0) {
			switch (key) {
				case SDL_SCANCODE_RETURN:
					Window::setResponseDelay(RESPONSE_DELAY);

					editing = false;
					break;

				case SDL_SCANCODE_BACKSPACE:
					if (cursorPos > 0) cursorPos--;

					[[fallthrough]];
				case SDL_SCANCODE_DELETE:
					text.erase(cursorPos, 1);

					Window::setResponseDelay(RESPONSE_DELAY_SHORT);
					break;

				case SDL_SCANCODE_LEFT:
					if (cursorPos > 0) cursorPos--;

					Window::setResponseDelay(RESPONSE_DELAY_SHORT);
					break;

				case SDL_SCANCODE_RIGHT:
					if (cursorPos < text.length() - 1) {
						cursorPos++;
					}

					Window::setResponseDelay(RESPONSE_DELAY_SHORT);
					break;
			}
		}
	}
}

void TextField::onKeyTyped(char c) {
	if (editing && hasWindowFocus) {
		if (Window::getResponseDelay() == 0) {
			if (cursorPos >= text.length()) {
				text += c;
			} else if (cursorPos < text.length()) {
				text[cursorPos] = c;
			}

			if (cursorPos < maxChars - 1) cursorPos++;

			Window::setResponseDelay(RESPONSE_DELAY);
		}
	}
}

void TextField::onFocusGained() {
	editing = true;

	Window::setResponseDelay(RESPONSE_DELAY);
}

void TextField::onFocusLost() {
	editing = false;
}

void TextField::onWindowFocusGained() {
	hasWindowFocus = true;
}

void TextField::onWindowFocusLost() {
	hasWindowFocus = false;
}

void TextField::setText(std::string_view newText) {
	text = newText;
}

std::string_view TextField::getText() {
	return text;
}