#include "MapRenderer.h"

MapRenderer::MapRenderer() {

}

void MapRenderer::drawBackground(PK2::Engine::GFX& gfx, int x, int y) {
	gfx.drawImage(imageBackground, x, y);
}

void MapRenderer::drawTileLayer(PK2::Engine::GFX& gfx, int layer, int startX, int startY, int endX, int endY) {
	if (map) {
		using PK2Map = PK2::Game::Map;

		// This should never happen, but we're just going to make sure that if it does, it won't crash the program
		
		// TODO This could be removed, if the start/end values get clamped, so that they are never going to reach these values.
		// TOOD If I'm going to remove this, I need to make sure to document this behavior in the header file and note that these values need to be clamped before using this method
		if (startX < 0) startX = 0;
		if (startY < 0) startY = 0;
		if (endX > map->getWidth() * PK2Map::TILE_SIZE) endX = map->getWidth() * PK2Map::TILE_SIZE;
		if (endY > map->getHeight() * PK2Map::TILE_SIZE) endY = map->getHeight() * PK2Map::TILE_SIZE;

		// TODO Check if endX/Y is below zero and if end < start? The programmer SHOULD know better than doing that...

		startX /= PK2Map::TILE_SIZE;
		startY /= PK2Map::TILE_SIZE;

		endX /= PK2Map::TILE_SIZE;
		endY /= PK2Map::TILE_SIZE;

		// Convert from screen position to map position by dividing by tile size
		for (int ty = startY; ty < (startY + endY); ty++) {
			for (int tx = startX; tx < (startX + endX); tx++) {
				int tileNumber = map->getTileAt(layer, tx, ty);

				// TODO Don't hardcode the empty tile id
				if (tileNumber != 255) {
					int tilesetX = (tileNumber % 10) * PK2Map::TILE_SIZE;
					int tilesetY = (tileNumber / 10) * PK2Map::TILE_SIZE;

					SDL_Rect tileSource = { tilesetX, tilesetY, PK2Map::TILE_SIZE , PK2Map::TILE_SIZE };
					SDL_Rect destination = { (tx - startX) * 32, (ty - startY) * 32, PK2Map::TILE_SIZE , PK2Map::TILE_SIZE };

					gfx.drawImage(imageTileset, tileSource, destination);
				}
			}
		}
	}
}

void MapRenderer::drawSpriteLayer(PK2::Engine::GFX& gfx, int layer, int startX, int startY, int startWidth, int startHeight) {
	if (map) {

	}
}

void MapRenderer::setMap(PK2::Game::Map& newMap) {
	this->map = &newMap;
}

void MapRenderer::setImageTileset(std::string_view tileset) {
	imageTileset = tileset;
}

void MapRenderer::setImageBackground(std::string_view background) {
	imageBackground = background;
}

void MapRenderer::setCamera(Camera* cam) {
	camera = cam;
}