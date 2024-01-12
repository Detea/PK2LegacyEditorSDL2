#pragma once
#include "GFX.h"
#include "Map.h"

#include <SDL.h>
#include <vector>

class MiniMap {
public:
	MiniMap();
	~MiniMap();

	void render(PK2::Engine::GFX& gfx);

	void setLayers(std::vector<std::vector<int>>* mapLayers);

	void updateMap(PK2::Game::Map& map);

	void setTilesetPixels(int* pixel, int tilesetWidth);
	
	// TODO This is garbage
	void updatePosition(int x, int y);
private:
	void generateMiniMapImage();

private:
	static constexpr unsigned char TILE_SWITCH2 = 146;
	static constexpr unsigned char TILE_SWITCH3 = 147;
	static constexpr unsigned char TILE_SWITCH1 = 145;
	static constexpr unsigned char TILE_START = 148;
	static constexpr unsigned char TILE_END = 149;

	static constexpr int MAP_WIDTH = 256;
	static constexpr int MAP_HEIGHT = 224;

	inline static SDL_Color bgColor { 0, 0, 0 };

	SDL_Point* mapPixels[MAP_WIDTH * MAP_HEIGHT];

	SDL_Texture* mapTexture = nullptr;

	std::vector<std::vector<int>>* layers = nullptr;

	int mapColors[150];

	int x = 0;
	int y = 0;
};

