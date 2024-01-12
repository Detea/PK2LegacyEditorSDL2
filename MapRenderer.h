#pragma once

#include "GFX.h"
#include "Map.h"
#include "Camera.h"

#include <vector>
#include <string>
#include <string_view>

class MapRenderer {
public:
	MapRenderer();

	void drawBackground(PK2::Engine::GFX& gfx, int x, int y);

	// Draws either the whole layer, if any of the start values is 0, or draws a specific portion of the layer that's within the specified dimension
	void drawTileLayer(PK2::Engine::GFX& gfx, int layer, int startX, int startY, int endX, int endY);

	// Same as drawTileLayer but for sprites
	void drawSpriteLayer(PK2::Engine::GFX& gfx, int layer, int startX = 0, int startY = 0, int startWidth = 0, int startHeight = 0);

	void setMap(PK2::Game::Map& map);

	// The game probably wouldn't need this, unless it would for some reason support the feature to change tilesets/backgrounds in the middle of play
	void setImageTileset(std::string_view tileset);
	void setImageBackground(std::string_view background);

	void setCamera(Camera* cam);

private:
	PK2::Game::Map* map = nullptr;

	std::string imageTileset = "";
	std::string imageBackground = "";

	Camera* camera = nullptr;
};