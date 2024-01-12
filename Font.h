#ifndef PK2_ENGINE_FONT_H
#define PK2_ENGINE_FONT_H

#include "PisteFontAttributes.h"

#include <string>
#include <string_view>

namespace PK2::Engine {
	class Font {
	public:
		Font();
		
		PisteFontAttributes& getFontAttributes();
		std::string& getFontImage();
	
		bool load(std::string_view fontFile);

		// The location/path where the font.txt file is located, without the file name.
		void setFontLocation(const std::string& path);
	private:
		PisteFontAttributes fontAttributes;

		std::string fontImage;
	};
}
#endif