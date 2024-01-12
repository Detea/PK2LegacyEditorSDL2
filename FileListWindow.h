#pragma once
#include "Window.h"
#include "Button.h"
#include "Link.h"
#include "ArrowsButton.h"
#include "FileBrowser.h"
#include "ContentPaths.h"

#include <string>

class FileListWindow : public Window {
public:
	FileListWindow(std::string title,
			 int x, int y,
			 int width, int height,

			 bool visible,

			 SDL_Scancode shortcutKey = PK2::Engine::Input::KEY_NONE,
			 SDL_Keymod shortcutMod = PK2::Engine::Input::MOD_NONE);

	virtual ~FileListWindow();

	void setContentPaths(PK2::Game::ContentPaths& paths);

private:
	void setupUI();

	void scrollFileListUp();
	void scrollFileListDown();

private:
	static constexpr int SEPARATOR_COLOR = 41;

	PK2::Game::ContentPaths contentPaths;

	Button* btnSave = nullptr;
	Button* btnMaps = nullptr;
	Button* btnTiles = nullptr;
	Button* btnSprites = nullptr;
	Button* btnScenery = nullptr;
	Button* btnMusic = nullptr;
	Button* btnHideDirectories = nullptr;

	ArrowsButton* scrollButton = nullptr;

	FileBrowser* fileListView = nullptr;
};

