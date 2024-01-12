#ifndef PK2_ENGINE_FILES_H
#define PK2_ENGINE_FILES_H

#include <string>
#include <string_view>
#include <filesystem>

namespace PK2::Engine {
	class Files final {
	public:
		inline static const std::string SEPARATOR = "/";

		static std::string getTileset(std::string_view file);
		static std::string getBackground(std::string_view file);

		static std::string getFontImage(std::string_view file);
		static std::string getFontAttributes(std::string_view file);

		static std::string getLanguage(std::string_view file);

		static void setGamePath(std::string_view path);

	private:
		inline static const std::string GFX_DIR = "gfx";
		inline static const std::string TILESET_DIR = GFX_DIR + SEPARATOR + "tiles" + SEPARATOR;
		inline static const std::string BACKGROUND_DIR = GFX_DIR + SEPARATOR + "scenery" + SEPARATOR;
		inline static const std::string LANGUAGE_DIR = "language" + SEPARATOR;
		inline static const std::string FONTS_DIR = LANGUAGE_DIR + "fonts" + SEPARATOR;

		inline static std::string gamePath;
	};
}
#endif