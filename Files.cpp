#include "Files.h"

using namespace PK2::Engine;

std::string Files::getTileset(std::string_view file) {
	return gamePath + TILESET_DIR + file.data();
}

std::string Files::getBackground(std::string_view file) {
	return gamePath + BACKGROUND_DIR + file.data();
}

std::string Files::getFontImage(std::string_view file) {
	return gamePath + FONTS_DIR + file.data();
}

std::string Files::getFontAttributes(std::string_view file) {
	return gamePath + FONTS_DIR + file.data();
}

std::string Files::getLanguage(std::string_view file) {
	return gamePath + LANGUAGE_DIR + file.data();
}

void Files::setGamePath(std::string_view path) {
	gamePath = path;
}