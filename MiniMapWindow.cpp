#include "MiniMapWindow.h"

MiniMapWindow::~MiniMapWindow() {
}

void MiniMapWindow::render(PK2::Engine::GFX& gfx) {
	if (visible) {
		Window::render(gfx);

		// TODO Should create a PaintComponent or something
		gfx.fillRect(x, y + 15, MAP_WIDTH, MAP_HEIGHT, bgColor);

		// TODO Foreground:  color_foreground != TILE_ESTO_ALAS)

		for (auto i = 0; i < layers->size(); i++) {
			for (int tx = 0; tx < MAP_WIDTH; tx++) {
				for (int ty = 0; ty < MAP_HEIGHT; ty++) {
					int tileID = layers->at(i).at(tx + MAP_WIDTH * ty);

					if (tileID != 255 && tileID < 150) {
						gfx.drawPoint(x + tx, y + 15 + ty, gfx.getColorInBackgroundPalette(mapColors[tileID]));
					}
				}
			}
		}

		for (int tx = 0; tx < MAP_WIDTH; tx++) {
			for (int ty = 0; ty < MAP_HEIGHT; ty++) {
				int spriteID = spritesLayer->at(tx + MAP_WIDTH * ty);

				if (spriteID != 255) {
					gfx.drawPoint(x + tx, y + 15 + ty, gfx.getColorInBackgroundPalette(231));
				}
			}
		}

		if (camera) {
			SDL_Color col = gfx.getColorInBackgroundPalette(31);
			gfx.drawRect(x + camera->x, y + 15 + camera->y, 48, 24, col);
		}
	}
}

void MiniMapWindow::updateMousePosition(int mouseX, int mouseY) {
	if (camera) {
		using Input = PK2::Engine::Input;

		if (Input::mouseDown(Input::MB_LEFT)) {
			if (mouseX >= x && mouseX <= x + width && mouseY >= 0 && mouseY <= y + height) {
				camera->x = (mouseX - x) - ((camera->width / 32) / 2);
				camera->y = (mouseY - y) - ((camera->height / 32) / 2);

			}
		}
	}
}

void MiniMapWindow::updateMap(PK2::Game::Map& map) {

}

void MiniMapWindow::setTilesetPixels(void* pixel, int tilesetWidth) {
	char* p = (char*)pixel;

	for (int tile = 0; tile < 150; tile++) {
		unsigned long primaryColor = 0;
		unsigned long averageShadow = 0;

		unsigned long number = 0;

		unsigned long primaryColors[9];
		for (int i = 0; i < 8; i++) {
			primaryColors[i] = 0;
		}

		unsigned char color = 0;
		for (int xx = 0; xx < 32; xx++) {
			for (int yy = 0; yy < 32; yy++) {
				int tileX = tile % 10;
				int tileY = tile / 10;

				color = (unsigned char)p[(xx + (tileX * 32)) + tilesetWidth * (yy + (tileY * 32))];

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
		mapColors[tile] = static_cast<unsigned char>(averageShadow + primaryColor * 32);
		//mapColors[tile] = averageShadow + primaryColor * 32;
	}
}

void MiniMapWindow::setLayers(std::vector<std::vector<int>>* layerData) {
	layers = layerData;
}

void MiniMapWindow::setSpritesLayer(std::vector<int>* layer) {
	spritesLayer = layer;
}

void MiniMapWindow::setCamera(Camera* cam) {
	camera = cam;
}