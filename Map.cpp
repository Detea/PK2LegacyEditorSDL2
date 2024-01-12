#include "Map.h"

PK2::Game::Map::Map() {

}

std::string_view PK2::Game::Map::getFileTileset() {
	return fileTileset;
}

std::string_view PK2::Game::Map::getFileBackground() {
	return fileBackground;
}

std::string_view PK2::Game::Map::getFileMusic() {
	return fileMusic;
}

std::string_view PK2::Game::Map::getName() {
	return name;
}

std::string_view PK2::Game::Map::getAuthor() {
	return author;
}

int PK2::Game::Map::getLevelNr() {
	return levelNr;
}

int PK2::Game::Map::getWeather() {
	return weather;
}

int PK2::Game::Map::getScrolling() {
	return scrolling;
}

int PK2::Game::Map::getTime() {
	return time;
}

int PK2::Game::Map::getPlayerSprite() {
	return playerSprite;
}

int PK2::Game::Map::getMapX() {
	return mapX;
}

int PK2::Game::Map::getMapY() {
	return mapY;
}

int PK2::Game::Map::getMapIcon() {
	return mapIcon;
}

int PK2::Game::Map::getTileAt(int layer, int x, int y) {
	int tile = 255;

	// TODO Use assert instead?
	if (layer >= 0 && layer < tileLayers.size() && (x + Map13Constants::MAP_WIDTH * y) < Map13Constants::MAP_SIZE) {
		tile = tileLayers.at(layer).at(x + Map13Constants::MAP_WIDTH * y);
	}

	return tile;
}

int PK2::Game::Map::getSpriteAt(int x, int y, int spriteLayer) {
	// TODO
	return 0;
}


void PK2::Game::Map::setFileTileset(std::string_view file) {
	fileTileset = file;
}

void PK2::Game::Map::setFileBackground(std::string_view file) {
	fileBackground = file;
}

void PK2::Game::Map::setFileMusic(std::string_view file) {
	fileMusic = file;
}

void PK2::Game::Map::setName(std::string_view mapName) {
	name = mapName;
}

void PK2::Game::Map::setAuthor(std::string_view authorName) {
	author = authorName;
}

void PK2::Game::Map::setLevelNr(int levelNumber) {
	levelNr = levelNumber;
}
	
void PK2::Game::Map::setWeather(int weatherId) {
	weather = weatherId;
}

void PK2::Game::Map::setScrolling(int scrollingType) {
	scrolling = scrollingType;
}
	
void PK2::Game::Map::setTime(int timeAmount) {
	time = timeAmount;
}

void PK2::Game::Map::setPlayerSprite(int playerSpriteIndex) {
	playerSprite = playerSpriteIndex;
}

void PK2::Game::Map::setMapX(int x) {
	mapX = x;
}

void PK2::Game::Map::setMapY(int y) {
	mapY = y;
}

void PK2::Game::Map::setMapIcon(int icon) {
	mapIcon = icon;
}

int PK2::Game::Map::getWidth() {
	return layerWidth;
}

int PK2::Game::Map::getHeight() {
	return layerHeight;
}

void PK2::Game::Map::setTileAt(int layer, int x, int y, int tile) {
	
}

void PK2::Game::Map::setSpriteAt(int x, int y, int spriteLayer) {
	// TODO
}

std::vector<std::string>& PK2::Game::Map::getSpriteFilenames() {
	return spriteFilenames;
}

void PK2::Game::Map::setVersion(unsigned char versionStr[5]) {
	versionString = "";

	int i = 0;
	unsigned char c = versionStr[0];

	while (i < 5) {
		c = versionStr[i];

		if (c != 0x0) {
			versionString += c;
		} else {
			break;
		}

		i++;
	}
}

std::string PK2::Game::Map::getVersionString() {
	return versionString;
}

const std::vector<int>& PK2::Game::Map::getLayer(int layer) {
	return tileLayers.at(layer);
}

void PK2::Game::Map::setTileLayer(int index, std::vector<int> data) {
	tileLayers.at(index) = data;
}

std::vector<std::vector<int>>* PK2::Game::Map::getTileLayers() {
	return &tileLayers;
}

std::vector<int>* PK2::Game::Map::getSpritesLayer() {
	return &spritesLayer;
}

void PK2::Game::Map::setSpritesLayer(std::vector<int>& layer) {
	spritesLayer = layer;
}