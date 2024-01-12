#ifndef PISTEFONT_ATTRIBUTE_H
#define PISTEFONT_ATTRIBUTE_H
#include "PisteLanguage.h"
#include <iostream>
#include <map>

namespace PK2::Engine {
	class PisteFontAttributes {
	public:
		PisteFontAttributes();
		PisteFontAttributes(PisteLanguage& languageFile);

		std::string getImageFile() const;

		// Width of the bitmap that contains the letters
		int getImageWidth() const;

		int getImageX() const;
		int getImageY() const;

		std::string_view getLetters() const;

		int getLetterWidth() const;
		int getLetterHeight() const;

		// Returns the x position of character c in the image file
		int getCharXOffset(char c) const;
	private:
		void setupOffsetTable();

	private:
		std::string imageFile;

		int imageWidth;
		int imageX;
		int imageY;

		std::string letters;

		int letterWidth;
		int letterHeight;

		std::map<char, int> charXOffsetMap;
	};
}
#endif