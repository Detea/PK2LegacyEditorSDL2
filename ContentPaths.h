#pragma once
#include <string>
#include <string_view>

#include <filesystem>

namespace PK2::Game {
	class ContentPaths {
	public:
		ContentPaths();
		ContentPaths(std::string_view basePath);

		// Returns true if the base path folder and the gfx, tiles, scenery and sprites folders exists, otherwise false
		bool setBase(std::string_view base);

		std::string_view getBase();

		std::string_view getTiles();
		std::string_view getBackgrounds();

		std::string_view getSprites();

		bool allPathsExist();

		std::string getFileTileset(std::string_view filename);
		std::string getFileBackground(std::string_view filename);

	private:
		static constexpr std::string_view GFX = "gfx";
		static constexpr std::string_view TILES = "tiles";
		static constexpr std::string_view SCENERY = "scenery";

		static constexpr std::string_view SPRITES = "sprites";

		// TODO Add support for content from episode folder

		std::string pathBase = "";

		std::string pathTiles = "";
		std::string pathBackgrounds = "";
		
		std::string pathSprites = "";

		std::filesystem::path basePath;
		std::filesystem::path tilesPath;
		std::filesystem::path backgroundsPath;
		std::filesystem::path spritesPath;
	};
}

