#include "MiniMap.h"

MiniMap::MiniMap() {
}

MiniMap::~MiniMap() {
	SDL_DestroyTexture(mapTexture);
	mapTexture = nullptr;
}

void MiniMap::render(PK2::Engine::GFX& gfx) {
	gfx.fillRect(0, 0, MAP_WIDTH, MAP_HEIGHT, bgColor);

	if (layers) {
		// TODO Clean this shit up and use constants and bla bla
		std::vector<int>& bgLayer = layers->at(0);

		for (int tileID = 0; tileID < bgLayer.size(); tileID++) {
			for (int tx = 0; tx < MAP_WIDTH; tx++) {
				for (int ty = 0; ty < MAP_HEIGHT; ty++) {
					int tile = bgLayer[tileID];

					if (tile != 255) {
						gfx.drawPoint(x + tx, y + ty, gfx.getColorInBackgroundPalette(mapColors[tile]));
					}
				}
			}
		}

		std::vector<int>& fgLayer = layers->at(1);

		for (int tileID = 0; tileID < fgLayer.size(); tileID++) {
			for (int tx = 0; tx < MAP_WIDTH; tx++) {
				for (int ty = 0; ty < MAP_HEIGHT; ty++) {
					int tile = fgLayer[tileID];

					if (tile != 255) {
						gfx.drawPoint(x + tx, y + ty, gfx.getColorInBackgroundPalette(mapColors[tile]));
					}
				}
			}
		}
	}
}

void MiniMap::updateMap(PK2::Game::Map& map) {

}

void MiniMap::setTilesetPixels(int* pixel, int tilesetWidth) {
	for (int tile = 0; tile < 150; tile++) {
		int primaryColor = 0;
		int averageShadow = 0;

		int number = 0;

		int primaryColors[9];
		for (int i = 0; i < 8; i++) {
			primaryColors[i] = 0;
		}

		unsigned char color = 0;
		for (int x = 0; x < 32; x++) {
			for (int y = 0; y < 32; y++) {
				int tileX = tile % 10;
				int tileY = tile / 10;

				color = pixel[x + (tileX * 32) + (y + tileY * 32) * tilesetWidth];

				if (color < 224) {
					primaryColor = color / 32;
					primaryColors[primaryColor] = primaryColors[primaryColor] + 1;

					averageShadow = averageShadow + (color % 32);

					number++;
				}
			}
		}

		primaryColor = 0;

		unsigned long primaryColorNr = 0;

		for (int i = 0; i < 8; i++) {
			if (primaryColors[i] > primaryColorNr) {
				primaryColor = i;
				primaryColorNr = primaryColors[i];
			}
		}

		if (number > 0) {
			averageShadow = averageShadow / number;
		} else {
			averageShadow = 0;
		}

		if (tile < 90) {
			averageShadow += 3;
		}

		if (tile == TILE_SWITCH1 ||
			tile == TILE_SWITCH2 ||
			tile == TILE_SWITCH3 ||
			tile == TILE_START ||
			tile == TILE_END) {
			averageShadow += 12;
		}

		if (averageShadow > 31) {
			averageShadow = 31;
		}

		// TODO Check if the cast is necessary
		//mapColors[tile] = static_cast<unsigned char>(averageShadow + primaryColor * 32);
		mapColors[tile] = averageShadow + primaryColor * 32;
	}
}

void MiniMap::generateMiniMapImage() {
	// https://wiki.libsdl.org/SDL2/SDL_LockTexture
}

void MiniMap::setLayers(std::vector<std::vector<int>>* mapLayers) {
	layers = mapLayers;
}

void MiniMap::updatePosition(int x, int y) {
	this->x = x;
	this->y = y;
}