#include "PisteFontAttributes.h"

using namespace PK2::Engine;

PisteFontAttributes::PisteFontAttributes() {

}

PisteFontAttributes::PisteFontAttributes(PisteLanguage& languageFile) {
	imageFile = std::string(languageFile.getText("image"));

	imageWidth = std::stoi(languageFile.getText("image width").data());
	imageX = std::stoi(languageFile.getText("image x").data());
	imageY = std::stoi(languageFile.getText("image y").data());

	letters = std::string(languageFile.getText("letters"));

	letterWidth = std::stoi(languageFile.getText("letter width").data());
	letterHeight = std::stoi(languageFile.getText("letter height").data());

	setupOffsetTable();
}

void PisteFontAttributes::setupOffsetTable() {
	for (int i = 0; i < letters.length(); i++) {
		charXOffsetMap[std::toupper(letters.data()[i])] = i * letterWidth;
	}
}

int PisteFontAttributes::getCharXOffset(char c) const {
	// Value only gets returned if it is present in the map, if it's not this method will return -1.
	return charXOffsetMap.count(std::toupper(c)) ? charXOffsetMap.at(std::toupper(c)) : -1;
}

std::string PisteFontAttributes::getImageFile() const {
	return imageFile;
}

int PisteFontAttributes::getImageWidth() const {
	return imageWidth;
}

int PisteFontAttributes::getImageX() const {
	return imageX;
}

int PisteFontAttributes::getImageY() const {
	return imageY;
}

std::string_view PisteFontAttributes::getLetters() const {
	return letters;
}

int PisteFontAttributes::getLetterWidth() const {
	return letterWidth;
}

int PisteFontAttributes::getLetterHeight() const {
	return letterHeight;
}