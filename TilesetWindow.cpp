#include "TilesetWindow.h"

#include "Map.h"
#include "Input.h"

TilesetWindow::~TilesetWindow() {

}

void TilesetWindow::render(PK2::Engine::GFX& gfx) {
	Window::render(gfx);

	gfx.drawImage(tilesetImage, x, y + 15);

	// TODO Clean this code up
	// TODO Use a functor/callback when selectedTile changes?

	// Draw the selection rectangle
	if (isFocused()) {
		using Map = PK2::Game::Map;
		using Input = PK2::Engine::Input;

		// Position of the mouse in tiles... (0, 1, 2, 3)
		int tx = ((Input::getMouseX() -  x) / Map::TILE_SIZE);
		int ty = ((Input::getMouseY() - (y + 15)) / Map::TILE_SIZE);

		// Adjusted mouse position in screen coordinates (0, 32, 64, 96)
		int mx = tx * Map::TILE_SIZE;
		int my = ty * Map::TILE_SIZE;

		SDL_Color bgColor = gfx.getColorInBackgroundPalette(SELECTION_RECT_BACKGROUND_COLOR);
		gfx.drawRect(x + mx + 1, y + 15 + my + 1, Map::TILE_SIZE, Map::TILE_SIZE, bgColor);

		SDL_Color foregroundColor = gfx.getColorInBackgroundPalette(SELECTION_RECT_FOREGROUND_COLOR);
		gfx.drawRect(x + mx, y + 15 + my, Map::TILE_SIZE, Map::TILE_SIZE, foregroundColor);

		gfx.drawStringTransparent(selectedTileStr, x + mx + 2, y + 15 + my + 2, 65);

		selectedTile = tx + ty * 10 + 1;

		selectedTileStr = std::to_string(selectedTile);
	}
}

void TilesetWindow::onClick(int clickX, int clickY) {
	Window::onClick(clickX, clickY);

	if (clickY > y + 15) {
		// TODO Shouldp pass the button via onClick, it's cleaner than using Input:: in here
		using Input = PK2::Engine::Input;

		if (Input::mouseDown(Input::MB_LEFT)) {
			using Map = PK2::Game::Map;

			int tx = (Input::getMouseX() / Map::TILE_SIZE);
			int ty = (Input::getMouseY() / Map::TILE_SIZE);

			selectedTile = tx + ty * 10 + 1;

			selectedTileStr = std::to_string(selectedTile);

			// TODO Reset selected sprite?

			Window::setResponseDelay(RESPONSE_DELAY);
		}
	}
}

void TilesetWindow::setTilesetImage(std::string_view file) {
	tilesetImage = file;
}

int TilesetWindow::getSelectedTile() {
	return selectedTile;
}