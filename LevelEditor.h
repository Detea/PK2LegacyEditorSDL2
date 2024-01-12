#pragma once
#include "GFX.h"
#include "PisteLanguage.h"
#include "PisteFontAttributes.h"
#include "Files.h"
#include "Logger.h"

#include "Window.h"
#include "LogWindow.h"
#include "FileListWindow.h"
#include "MapInfoWindow.h"
#include "TilesetWindow.h"
#include "MiniMapWindow.h"

#include "UI.h"

#include "Camera.h"

#include "StdLogOutput.h"
#include "LevelEditorLogOutput.h"

#include "ContentPaths.h"

#include "MapReader.h"
#include "MapReader13.h"
#include "MapRenderer.h"
#include "Map.h"

#include <string>
#include <string_view>
#include <vector>

class LevelEditor {
public:
	LevelEditor();
	~LevelEditor();

	void init(PK2::Engine::GFX& gfx);

	void render(PK2::Engine::GFX& gfx);
	void update();

	void keyPressed(SDL_Scancode key, Uint16 mod);

	virtual void onKeyTyped(char c);

	std::string_view getPK2Path();

	void loadMap(std::string_view filename);

private:
	void createWindows();

	void onLog();

	void loadPK2Path();

private:
	static constexpr int BACKGROUND_COLOR = 37;

	static constexpr std::string_view PK2_INI_FILE = "pk2le_dir.ini";

	UI ui;

	LogWindow* logWindow = nullptr;

	MapInfoWindow* mapInfoWindow = nullptr;

	FileListWindow* fileListWindow = nullptr;

	TilesetWindow* tilesetWindow = nullptr;

	MiniMapWindow* miniMapWindow = nullptr;

	PK2::Engine::PisteFontAttributes fontAttributes;

	std::string mapFilename = "";
	PK2::Game::MapReader13 mapReader13;
	PK2::Game::MapReader* mapReader = &mapReader13;

	std::string fontImageFile;
	std::string editorGFXFile;

	PK2::Engine::StdLogOutput stdLogOut;
	LevelEditorLogOutput leOutput;

	std::string pk2Path;
	std::string fileTileset;
	std::string fileBackground;

	PK2::Game::Map loadedMap;
	MapRenderer mapRenderer;

	PK2::Game::ContentPaths contentPaths;

	Camera camera;
};

