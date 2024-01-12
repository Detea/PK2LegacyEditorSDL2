#pragma once
#include "Window.h"
#include "Map.h"
#include "Label.h"
#include "ArrowsButton.h"
#include "TextField.h"
#include "Button.h"

#include "Scrolling.h"
#include "Weather.h"

#include <string>
#include <string_view>

class MapInfoWindow : public Window {
public:
	MapInfoWindow(std::string title,
			 int x, int y,
			 int width, int height,

			 bool visible,

			 SDL_Scancode shortcutKey = PK2::Engine::Input::KEY_NONE,
			 SDL_Keymod shortcutMod = PK2::Engine::Input::MOD_NONE);

	virtual ~MapInfoWindow();

	// Passes the currently loaded map and it's filename ('name'.map) to the MapInfoWindow
	void setMap(PK2::Game::Map* currentMap, std::string_view filename);

private:
	void setupUI();

	std::string getScrollingDescription(int scrolling);
	std::string getWeatherDescription(int weather);

private:
	inline static std::string scrollingDescriptions[4] = {
		"no scrolling  ",
		"up and down   ",
		"left and right",
		"free scrolling"
	};

	inline static std::string weatherDescriptions[5] = {
		"normal       ",
		"rain         ",
		"leaves       ",
		"rain + leaves",
		"snow         "
	};

	int newScrollingValue = 0;
	int newWeatherValue = 0;

	PK2::Game::Map* map = nullptr;
	std::string mapFilename = "";

	Label* lblVersionStr = nullptr;

	Label* lblLevelNrVal = nullptr;
	Label* lblTimeVal = nullptr;

	Label* lblTilesetVal = nullptr;
	Label* lblBackgroundVal = nullptr;

	Label* lblMapIconVal = nullptr;
	Label* lblMapXVal = nullptr;
	Label* lblMapYVal = nullptr;

	TextField* tfMapName = nullptr;
	TextField* tfFilename = nullptr;
	TextField* tfAuthor = nullptr;
	TextField* tfMusicFile = nullptr;

	Button* btnScrolling = nullptr;
	Button* btnWeather = nullptr;
};

