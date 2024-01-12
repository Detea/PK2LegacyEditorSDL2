#include "Label.h"

#include <iostream>

Label::Label(const std::string& text, int x, int y) : Component(x, y) {
	setText(text);
}

Label::Label(const std::string& text, PK2::Engine::Font& font) {
	setFont(font);
	setText(text);
}

Label::~Label() {
}

void Label::setText(std::string_view text) {
	this->text = text;

	width = font.getFontAttributes().getLetterWidth() * text.length();
	height = font.getFontAttributes().getLetterHeight();
}

void Label::draw(PK2::Engine::GFX& gfx) {
	if (visible) gfx.drawString(text, x, y);
}