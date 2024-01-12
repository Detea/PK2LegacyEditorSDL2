#pragma once
#include "Window.h"

#include <string>
#include <string_view>

class TilesetWindow : public Window {
public:
	using Window::Window;

	virtual ~TilesetWindow();

	virtual void render(PK2::Engine::GFX& gfx) override;
	virtual void onClick(int clickX, int clickY) override;

	void setTilesetImage(std::string_view file);

	int getSelectedTile();

private:
	static constexpr int RESPONSE_DELAY = 15;

	static constexpr int SELECTION_RECT_FOREGROUND_COLOR = 120;
	static constexpr int SELECTION_RECT_BACKGROUND_COLOR = 0;

	std::string tilesetImage;
	std::string selectedTileStr = "";

	int selectedTile = 0;
};

