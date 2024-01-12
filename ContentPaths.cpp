#include "ContentPaths.h"

#include <filesystem>
#include <iostream>

using namespace PK2::Game;

ContentPaths::ContentPaths() {

}

ContentPaths::ContentPaths(std::string_view basePath) {
	setBase(basePath);
}

bool ContentPaths::setBase(std::string_view base) {
	basePath = std::filesystem::path(base);

	// Again, ideally you'd check if all the path existed. Probably at startup.

	pathBase = basePath.generic_string();
	
	tilesPath = std::filesystem::path(basePath);
	tilesPath /= GFX;
	tilesPath /= TILES;

	pathTiles = tilesPath.generic_string();

	backgroundsPath = std::filesystem::path(basePath);
	backgroundsPath /= GFX;
	backgroundsPath /= SCENERY;

	pathBackgrounds = backgroundsPath.generic_string();

	spritesPath = std::filesystem::path(basePath);
	spritesPath /= SPRITES;

	pathSprites = spritesPath.generic_string();

	// TODO Check for music and maps
	return allPathsExist();
}

bool ContentPaths::allPathsExist() {
	return std::filesystem::exists(basePath) &&
		std::filesystem::exists(tilesPath) &&
		std::filesystem::exists(backgroundsPath) &&
		std::filesystem::exists(spritesPath);
}

std::string_view ContentPaths::getBase() {
	return pathBase;
}

std::string_view ContentPaths::getTiles() {
	return pathTiles;
}

std::string_view ContentPaths::getBackgrounds() {
	return pathBackgrounds;
}

std::string_view ContentPaths::getSprites() {
	return pathSprites;
}

std::string ContentPaths::getFileTileset(std::string_view filename) {
	std::filesystem::path filePath = tilesPath;
	filePath /= filename;

	return filePath.string();
}

std::string ContentPaths::getFileBackground(std::string_view filename) {
	std::filesystem::path filePath = backgroundsPath;
	filePath /= filename;

	return filePath.string();
}