#include "MapReader13.h"
#include "Map13Constants.h"

#include "Logger.h"

#include <fstream>

#include <iostream>

using MapReader13 = PK2::Game::MapReader13;
using Logger = PK2::Engine::Logger;

MapReader13::MapReader13() {

}

void MapReader13::read(PK2::Game::Map& mapTarget, std::string_view filename) {
	std::ifstream in(filename.data(), std::ios::binary);

	if (!in) {
		Logger::warn("Unable to load map file.", "MapReader13");
	} else {
		unsigned char version[5];

		in.read(reinterpret_cast<char *>(&version), sizeof(version));

		if (!versionMatch(Map13Constants::VERSION_ID, version)) {
			Logger::error("Provided map is not of version 1.3!");
		} else {
			resetLayers(mapTarget);

			mapTarget.setVersion(version);

			std::string tileset = readString(in, Map13Constants::FILE_LENGTH);
			std::string background = readString(in, Map13Constants::FILE_LENGTH);
			std::string music = readString(in, Map13Constants::FILE_LENGTH);
			
			std::string name = readString(in, Map13Constants::NAME_AUTHOR_STR_LENGTH);
			std::string author = readString(in, Map13Constants::NAME_AUTHOR_STR_LENGTH);
			
			int levelNr = readPK2Int(in);
			int weather = readPK2Int(in);

			int switch1Value = readPK2Int(in);
			int switch2Value = readPK2Int(in);
			int switch3Value = readPK2Int(in);

			int time = readPK2Int(in);

			int extra = readPK2Int(in); // unused

			int scrolling = readPK2Int(in);

			int playerSprite = readPK2Int(in);

			int mapX = readPK2Int(in);
			int mapY = readPK2Int(in);
			int mapIcon = readPK2Int(in);

			int spritesAmount = readPK2Int(in);

			// Might want to put these strings directly into mapTarget? Maybe after error checking?
			std::vector<std::string> spritesList;

			for (int i = 0; i < spritesAmount; i++) {
				spritesList.push_back(readString(in, Map13Constants::FILE_LENGTH));
			}

			std::vector<int> layerBackground(Map13Constants::MAP_SIZE);
			readLayer(in, layerBackground, Map13Constants::MAP_WIDTH, Map13Constants::MAP_HEIGHT);

			std::vector<int> layerForeground(Map13Constants::MAP_SIZE);
			readLayer(in, layerForeground, Map13Constants::MAP_WIDTH, Map13Constants::MAP_HEIGHT);
		
			std::vector<int> layerSprites(Map13Constants::MAP_SIZE);
			readLayer(in, layerSprites, Map13Constants::MAP_WIDTH, Map13Constants::MAP_HEIGHT);

			mapTarget.setFileTileset(tileset);
			mapTarget.setFileBackground(background);
			mapTarget.setFileMusic(music);
			
			mapTarget.setName(name);
			mapTarget.setAuthor(author);

			mapTarget.setLevelNr(levelNr);
			mapTarget.setWeather(weather);

			// TODO set switch times

			mapTarget.setTime(time);

			// TODO Set extra?

			mapTarget.setScrolling(scrolling);

			mapTarget.setPlayerSprite(playerSprite);

			mapTarget.setMapX(mapX);
			mapTarget.setMapY(mapY);
			mapTarget.setMapIcon(mapIcon);

			mapTarget.setTileLayer(Map13Constants::LAYER_BACKGROUND, layerBackground);
			mapTarget.setTileLayer(Map13Constants::LAYER_FOREGROUND, layerForeground);

			mapTarget.setSpritesLayer(layerSprites);

			Logger::info(tileset);
			Logger::info(author);
		}
	}
}

void MapReader13::resetLayers(PK2::Game::Map& mapTarget) {
	// Remove all previously loaded layers

	// Tile layers
	std::vector<int> emptyLayer(Map13Constants::MAP_SIZE);
	std::fill(emptyLayer.begin(), emptyLayer.end(), 255);

	mapTarget.getTileLayers()->clear();
	mapTarget.getTileLayers()->push_back(emptyLayer);
	mapTarget.getTileLayers()->push_back(emptyLayer);

	// TODO Sprites
	// Sprite layers

	/*
	* Rewrite this shit, there's a leak in here somewhere
	* 
	std::vector<std::vector<int>>* layers = mapTarget.getAllTileLayers();
	layers->clear();

	// TODO Optimization: if the layers were already set before and have the capacity of MAP_SIZE, reuse them instead?

	std::vector<int> tmpLayer(Map13Constants::MAP_SIZE);

	layers->push_back(tmpLayer);
	layers->push_back(tmpLayer);

	auto& backgroundLayer = layers->at(Map13Constants::LAYER_BACKGROUND);
	auto& foregroundLayer = layers->at(Map13Constants::LAYER_FOREGROUND);

	backgroundLayer.reserve(Map13Constants::MAP_SIZE);
	foregroundLayer.reserve(Map13Constants::MAP_SIZE);

	// Fill both layers with the empty tile
	//std::fill(backgroundLayer.begin(), backgroundLayer.end(), Map13Constants::TILE_EMPTY);
	//std::fill(backgroundLayer.begin(), backgroundLayer.end(), Map13Constants::TILE_EMPTY);

	// Do the same with the sprite layer
	auto& spritesLayer = mapTarget.getAllSpriteLayers();
	spritesLayer.clear();

	spritesLayer.push_back(tmpLayer);
	
	auto& firstSpriteLayer = spritesLayer[0];
	firstSpriteLayer.reserve(Map13Constants::MAP_SIZE);

	//std::fill(firstSpriteLayer.begin(), firstSpriteLayer.end(), Map13Constants::TILE_EMPTY);
	*/
}