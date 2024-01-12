#pragma once
#include "GFX.h"
#include "Map.h"
#include "Window.h"
#include "Map13Constants.h"

#include "Camera.h"

#include <SDL.h>
#include <vector>

class MiniMapWindow : public Window {
public:
	using Window::Window;

	virtual ~MiniMapWindow();

	virtual void render(PK2::Engine::GFX& gfx) override;

	// TODO Maybe just add a setMap() method?
	void setLayers(std::vector<std::vector<int>>* layers);
	void setSpritesLayer(std::vector<int>* spritesLayer);

	void updateMap(PK2::Game::Map& map);

	void setTilesetPixels(void* pixel, int tilesetWidth);

	void updateMousePosition(int mouseX, int mouseY) override;

	void setCamera(Camera* cam);

private:
	static constexpr unsigned char TILE_SWITCH2 = 146;
	static constexpr unsigned char TILE_SWITCH3 = 147;
	static constexpr unsigned char TILE_SWITCH1 = 145;
	static constexpr unsigned char TILE_START = 148;
	static constexpr unsigned char TILE_END = 149;

	static constexpr int MAP_WIDTH = 256;
	static constexpr int MAP_HEIGHT = 224;

	inline static SDL_Color bgColor{ 0, 0, 0 };

	SDL_Point* mapPixels[MAP_WIDTH * MAP_HEIGHT];

	SDL_Texture* mapTexture = nullptr;

	std::vector<std::vector<int>>* layers = nullptr;
	std::vector<int>* spritesLayer = nullptr;

	Camera* camera = nullptr;

	int mapColors[150];
};

