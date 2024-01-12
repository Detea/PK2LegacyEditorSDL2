#pragma once

#include "Weather.h"
#include "Scrolling.h"
#include "Map13Constants.h"

#include <string>
#include <string_view>
#include <vector>
#include <array>

namespace PK2::Game {
	class Map {
	public:
		Map();

		std::string_view getFileTileset();
		std::string_view getFileBackground();
		std::string_view getFileMusic();
		
		std::string_view getName();
		std::string_view getAuthor();

		int getLevelNr();

		int getWeather();
		int getScrolling();

		int getTime();

		int getPlayerSprite();

		int getMapX();
		int getMapY();
		int getMapIcon();

		int getTileAt(int layer, int x, int y);

		// spriteLayer is the last parameter in this method, so that it can have a default value, for convinience. The original map format only has one sprite layer.
		int getSpriteAt(int x, int y, int spriteLayer = 0);


		void setFileTileset(std::string_view file);
		void setFileBackground(std::string_view file);
		void setFileMusic(std::string_view file);

		void setName(std::string_view mapName);
		void setAuthor(std::string_view author);

		void setLevelNr(int levelNr);

		void setWeather(int weather);
		void setScrolling(int scrolling);

		void setTime(int time);

		void setPlayerSprite(int playerSprite);

		void setMapX(int x);
		void setMapY(int y);
		void setMapIcon(int icon);

		/*
			Returns the tile at x, y in layer "layer".
			
			NOTE: This method does not check if x, y and layer are valid.
			Meaning it won't check if any of these values are < 0 or > map width/height, etc.
			Make sure these values are valid, before passing them.
		*/
		void setTileAt(int layer, int x, int y, int tile);

		// spriteLayer is the last parameter in this method, so that it can have a default value, for convinience. The original map format only has one sprite layer.
		void setSpriteAt(int x, int y, int spriteLayer = 0);

		std::vector<int>* getSpritesLayer();
		void setSpritesLayer(std::vector<int>& layer);

		const std::vector<int>& getLayer(int layer);
		void setTileLayer(int index, std::vector<int> data);
		std::vector<std::vector<int>>* getTileLayers();

		std::vector<std::string>& getSpriteFilenames();

		static int getWidth();
		static int getHeight();

		void setVersion(unsigned char versionStr[5]);
		std::string getVersionString();

	public:
		static constexpr int TILE_SIZE = 32; // width and height of the tiles

	protected:
		unsigned char versionChar[5];
		std::string versionString;

		std::string fileTileset;
		std::string fileBackground;
		std::string fileMusic;

		// Name of the map
		std::string name;
		std::string author;

		// Number of the level in the episode it belongs to
		int levelNr = 1;

		int weather = Weather::NORMAL;

		int scrolling = Scrolling::STATIC;

		int time = 0;

		int playerSprite = 0;

		int mapX = 0;
		int mapY = 0;
		int mapIcon = 0;

		// Not sure if this is ever going to change, but I'm just going to put this here for now
		inline static int layerWidth = Map13Constants::MAP_WIDTH;
		inline static int layerHeight = Map13Constants::MAP_HEIGHT;

		std::vector<std::vector<int>> tileLayers;
		std::vector<int> spritesLayer;

		std::vector<std::string> spriteFilenames;
	};
}