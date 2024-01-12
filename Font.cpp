#include "Font.h"

#include "PisteLanguage.h"
#include "Logger.h"

using namespace PK2::Engine;

Font::Font() {

}

bool Font::load(std::string_view fontFile) {
	PisteLanguage lang;

	if (!lang.readFile(fontFile)) {
		Logger::error("Unable to load font file: " + std::string(fontFile));

		return false;
	}

	fontAttributes = PisteFontAttributes(lang);
	fontImage = fontAttributes.getImageFile(); // TODO How to handle paths? Should this only store the image file itself or the whole path to it?

	return true;
}

void Font::setFontLocation(const std::string& path) {
	fontImage = path + fontAttributes.getImageFile();
}

PisteFontAttributes& Font::getFontAttributes() {
	return fontAttributes;
}

std::string& Font::getFontImage() {
	return fontImage;
}